
Skip to content
This repository

    Pull requests
    Issues
    Gist

    @Heedx

2
1

    0

MyRobotLab/mrlcomm
Code
Issues 1
Pull requests 0
Projects 0
Wiki
Pulse
Graphs
mrlcomm/MrlComm.cpp
c59c492 on Nov 27, 2016
@supertick supertick worky yay!
504 lines (431 sloc) 14.3 KB
#include "Msg.h"
#include "Device.h"
#include "Pin.h"
#include "MrlNeopixel.h"
#include "Servo.h"
#include "MrlServo.h"
#include "MrlI2cBus.h"
#include "MrlUltrasonicSensor.h"
#include "LinkedList.h"
#include "MrlComm.h"

/**
 <pre>
 Schema Type Conversions
 Schema      ARDUINO					Java							Range
 none		byte/unsigned char		int (cuz Java byte bites)		1 byte - 0 to 255
 boolean	boolean					boolean							0 1
 b16		int						int (short)						2 bytes	-32,768 to 32,767
 b32		long					int								4 bytes -2,147,483,648 to 2,147,483, 647
 bu32		unsigned long			long							0 to 4,294,967,295
 str		char*, size				String							variable length
 []			byte[], size			int[]							variable length
 </pre>
 */

MrlComm::MrlComm() {
	msg = Msg::getInstance(this);
	softReset();
}

MrlComm::~MrlComm() {
}

/***********************************************************************
 * PUBLISH_BOARD_STATUS
 * This function updates the average time it took to run the main loop
 * and reports it back with a publishBoardStatus MRLComm message
 *
 * TODO: avgTiming could be 0 if loadTimingModule = 0 ?!
 *
 * MAGIC_NUMBER|7|[loadTime long0,1,2,3]|[freeMemory int0,1]
 */
void MrlComm::publishBoardStatus() {

	// protect against a divide by zero in the division.
	if (publishBoardStatusModulus == 0) {
		publishBoardStatusModulus = 10000;
	}

	unsigned int avgTiming = 0;
	unsigned long now = micros();

	avgTiming = (now - lastMicros) / publishBoardStatusModulus;

	// report board status
	if (boardStatusEnabled && (loopCount % publishBoardStatusModulus == 0)) {
		byte deviceSummary[deviceList.size() * 2];
		for (int i = 0; i < deviceList.size(); ++i) {
			deviceSummary[i] = deviceList.get(i)->id;
			deviceSummary[i + 1] = deviceList.get(i)->type;
		}
		msg->publishBoardStatus(avgTiming, getFreeRam(), deviceSummary, deviceList.size() * 2);
	}
	// update the timestamp of this update.
	lastMicros = now;
}

int MrlComm::getFreeRam() {
	// KW: In the future the arduino might have more than an 32/64k of ram. an int might not be enough here to return.
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

/**
 * getDevice - this method will look up a device by it's id in the device list.
 * it returns null if the device isn't found.
 */
Device* MrlComm::getDevice(int id) {
	ListNode<Device*>* node = deviceList.getRoot();
	while (node != NULL) {
		if (node->data->id == id) {
			return node->data;
		}
		node = node->next;
	}

	msg->publishError(F("device does not exist"));
	return NULL; //returning a NULL ptr can cause runtime error
	// you'll still get a runtime error if any field, member or method not
	// defined is accessed
}
/**
 * This adds a device to the current set of active devices in the deviceList.
 * 
 * FIXME - G: I think dynamic array would work better
 * at least for the deviceList
 * TODO: KW: i think it's pretty dynamic now.
 * G: the nextDeviceId & Id leaves something to be desired - and the "index" does
 * not spin through the deviceList to find it .. a dynamic array of pointers would only
 * expand if it could not accomidate the current number of devices, when a device was
 * removed - the slot could be re-used by the next device request
 */
Device* MrlComm::addDevice(Device* device) {
	deviceList.add(device);
	return device;
}

/***********************************************************************
 * UPDATE DEVICES BEGIN
 * updateDevices updates each type of device put on the device list
 * depending on their type.
 * This method processes each loop. Typically this "back-end"
 * processing will read data from pins, or change states of non-blocking
 * pulses, or possibly regulate a motor based on pid values read from
 * pins
 */
void MrlComm::updateDevices() {

	// update self - the first device which
	// is type Arduino
	update();

	ListNode<Device*>* node = deviceList.getRoot();
	// iterate through our device list and call update on them.
	while (node != NULL) {
		node->data->update();
		node = node->next;
	}
}

/***********************************************************************
 * UPDATE BEGIN
 * updates self - reads from the pinList both analog and digital
 * sends pin data back
 */
void MrlComm::update() {
	unsigned long now = millis();
	if ((now - lastHeartbeatUpdate > 1000) && heartbeatEnabled) {
		softReset();
		lastHeartbeatUpdate = now;
		return;
	}

	if (pinList.size() > 0) {

		// size of payload - 1 byte for address + 2 bytes per pin read
		// this is an optimization in that we send back "all" the read pin data in a
		// standard 2 byte package - digital reads don't need both bytes, but the
		// sending it all back in 1 msg and the simplicity is well worth it
		// msg.addData(pinList.size() * 3 /* 1 address + 2 read bytes */);

		ListNode<Pin*>* node = pinList.getRoot();
		// iterate through our device list and call update on them.
		unsigned int dataCount = 0;
		while (node != NULL) {
			Pin* pin = node->data;
			if (pin->rate == 0 || (now > pin->lastUpdate + (1000 / pin->rate))) {
				pin->lastUpdate = now;
				// TODO: move the analog read outside of this method and pass it in!
				if (pin->type == ANALOG) {
					pin->value = analogRead(pin->address);
				} else {
					pin->value = digitalRead(pin->address);
				}

				// loading both analog & digital data
				msg->add(pin->address); // 1 byte
				msg->add16(pin->value); // 2 byte b16 value

				++dataCount;
			}
			node = node->next;
		}
		if (dataCount) {
			msg->publishPinArray(msg->getBuffer(), msg->getBufferSize());
		}
	}
}

int MrlComm::getCustomMsgSize() {
	return customMsgSize;
}

void MrlComm::processCommand() {
	msg->processCommand();
	if (ackEnabled) {
		msg->publishAck(1);
	}
}

void MrlComm::enableAck(bool enabled) {
	ackEnabled = enabled;
}

bool MrlComm::readMsg() {
	return msg->readMsg();
}

void MrlComm::begin(HardwareSerial& serial) {

	// TODO: the arduino service might get a few garbage bytes before we're able
	// to run, we should consider some additional logic here like a "publishReset"
	// publish version on startup so it's immediately available for mrl.
	// TODO: see if we can purge the current serial port buffers

	while (!serial) {
		; // wait for serial port to connect. Needed for native USB
	}

	// clear serial
	serial.flush();

	msg->begin(serial);

	// send 3 boardInfos to PC to announce,
	// Hi I'm an Arduino with version x, board type y, and I'm ready :)
	for (int i = 0; i < 5; ++i) {
		msg->publishBoardInfo(MRLCOMM_VERSION, BOARD);
		serial.flush();
	}
}

/****************************************************************
 *               GENERATED METHOD INTERFACE BEGIN
 * All methods signatures below this line are controlled by arduinoMsgs.schema
 * The implementation contains custom logic - but the signature is generated
 *
 */

// > getBoardInfo
void MrlComm::getBoardInfo() {
	msg->publishBoardInfo(MRLCOMM_VERSION, BOARD);
}

// > echo/str name1/b8/bu32 bui32/b32 bi32/b9/str name2/[] config/bu32 bui322
/*
 void MrlComm::echo(long sInt, byte name1Size, const char*name1, byte b8,
 unsigned long bui32, long bi32, byte b9, byte name2Size,
 const char*name2, byte configSize, const byte*config,
 unsigned long bui322) {
 */
void MrlComm::echo(unsigned long b32) {
	msg->publishEcho(b32);
}

// > controllerAttach/serialPort
// TODO - talk to calamity
void MrlComm::controllerAttach(byte serialPort) {
	msg->publishDebug(String("controllerAttach " + String(serialPort)));
}

// > customMsg/[] msg
// from PC --> loads customMsg buffer
void MrlComm::customMsg(byte msgSize, const byte*msg) {
	for (byte i = 0; i < msgSize && msgSize < 64; i++) {
		customMsgBuffer[i] = msg[i];	// *(msg + i);
	}
	customMsgSize = msgSize;
}

/**
 * deviceDetach - get the device
 * if it exists delete it and remove it from the deviceList
 */
// > deviceDetach/deviceId
void MrlComm::deviceDetach(byte id) {
	ListNode<Device*>* node = deviceList.getRoot();
	int index = 0;
	while (node != NULL) {
		if (node->data->id == id) {
			delete node->data;
			deviceList.remove(index);
			break;
		}
		node = node->next;
		index++;
	}
}

// > disablePin/pin
void MrlComm::disablePin(byte address) {
	ListNode<Pin*>* node = pinList.getRoot();
	int index = 0;
	while (node != NULL) {
		if (node->data->address == address) {
			delete node->data;
			pinList.remove(index);
			break;
		}
		node = node->next;
		index++;
	}
}

// > disablePins
void MrlComm::disablePins() {
	while (pinList.size() > 0) {
		delete pinList.pop();
	}
}

// > enableBoardStatus
void MrlComm::enableBoardStatus(bool enabled) {
	// msg->publishDebug("enableBoardStatus");
	boardStatusEnabled = enabled;
}

// > enableHeartbeat/bool enabled
void MrlComm::enableHeartbeat(bool enabled) {
	heartbeatEnabled = enabled;
}

// > enablePin/address/type/b16 rate
void MrlComm::enablePin(byte address, byte type, int rate) {
	// don't add it twice
	for (int i = 0; i < pinList.size(); ++i) {
		Pin* pin = pinList.get(i);
		if (pin->address == address) {
			// TODO already exists error?
			break;
		}
	}

	if (type == DIGITAL) {
		pinMode(address, INPUT);
	}
	Pin* p = new Pin(address, type, rate);
	p->lastUpdate = 0;
	pinList.add(p);
}

// > heartbeat
void MrlComm::heartbeat() {
	lastHeartbeatUpdate = millis();
}

// > i2cBusAttach/deviceId/i2cBus
void MrlComm::i2cBusAttach(byte deviceId, byte i2cBus) {
	// @Mats - do you need deviceType & deviceAddress here ?
	// if not we should shorten the i2cAttach parameters :)
	MrlI2CBus* i2cbus = (MrlI2CBus*) addDevice(new MrlI2CBus(deviceId));
	i2cbus->attach(i2cBus);
}

// > i2cRead/deviceId/deviceAddress/size
void MrlComm::i2cRead(byte deviceId, byte deviceAddress, byte size) {
	((MrlI2CBus*) getDevice(deviceId))->i2cRead(deviceAddress, size);
}

// > i2cWrite/deviceId/deviceAddress/[] data
void MrlComm::i2cWrite(byte deviceId, byte deviceAddress, byte dataSize, const byte*data) {
	((MrlI2CBus*) getDevice(deviceId))->i2cWrite(deviceAddress, dataSize, data);
}

// > i2cWriteRead/deviceId/deviceAddress/readSize/writeValue
void MrlComm::i2cWriteRead(byte deviceId, byte deviceAddress, byte readSize, byte writeValue) {
	((MrlI2CBus*) getDevice(deviceId))->i2cWriteRead(deviceAddress, readSize, writeValue);
}

// > neoPixelAttach/pin/b16 numPixels
void MrlComm::neoPixelAttach(byte deviceId, byte pin, long numPixels) {
	MrlNeopixel* neo = (MrlNeopixel*) addDevice(new MrlNeopixel(deviceId));
	neo->attach(pin, numPixels);
}

// > neoPixelAttach/pin/b16 numPixels
void MrlComm::neoPixelSetAnimation(byte deviceId, byte animation, byte red, byte green, byte blue, int speed) {
	((MrlNeopixel*) getDevice(deviceId))->setAnimation(animation, red, green, blue, speed);
}

// > neoPixelWriteMatrix/deviceId/[] buffer
void MrlComm::neoPixelWriteMatrix(byte deviceId, byte bufferSize, const byte*buffer) {
	((MrlNeopixel*) getDevice(deviceId))->neopixelWriteMatrix(bufferSize, buffer);
}

// > servoAttach/deviceId/pin/targetOutput/b16 velocity
void MrlComm::servoAttach(byte deviceId, byte pin, byte targetOutput, int velocity) {
	MrlServo* servo = new MrlServo(deviceId);
	addDevice(servo);
	// not your mama's attach - this is attaching/initializing the MrlDevice
	servo->attach(pin, targetOutput, velocity);
}

// > servoEnablePwm/deviceId/pin
void MrlComm::servoEnablePwm(byte deviceId, byte pin) {
	MrlServo* servo = (MrlServo*) getDevice(deviceId);
	servo->enablePwm(pin);
}

// > servoDisablePwm/deviceId
void MrlComm::servoDisablePwm(byte deviceId) {
	MrlServo* servo = (MrlServo*) getDevice(deviceId);
	servo->disablePwm();
}

// > servoSetMaxVelocity/deviceId/b16 maxVelocity
void MrlComm::servoSetMaxVelocity(byte deviceId, int maxVelocity) {
	MrlServo* servo = (MrlServo*) getDevice(deviceId);
	servo->setMaxVelocity(maxVelocity);
}

// > servoSetVelocity/deviceId/b16 velocity
void MrlComm::servoSetVelocity(byte deviceId, int velocity) {
	MrlServo* servo = (MrlServo*) getDevice(deviceId);
	servo->setVelocity(velocity);
}

void MrlComm::servoSweepStart(byte deviceId, byte min, byte max, byte step) {
	MrlServo* servo = (MrlServo*) getDevice(deviceId);
	servo->startSweep(min, max, step);
}

void MrlComm::servoSweepStop(byte deviceId) {
	MrlServo* servo = (MrlServo*) getDevice(deviceId);
	servo->stopSweep();
}

void MrlComm::servoWrite(byte deviceId, byte target) {
	msg->publishDebug("MrlComm::servoWrite - servoWrite" + String(deviceId));
	MrlServo* servo = (MrlServo*) getDevice(deviceId);
	msg->publishDebug("got - servoWrite" + String(deviceId));
	servo->servoWrite(target);
	msg->publishDebug("got - wrote" + String(deviceId));
}

void MrlComm::servoWriteMicroseconds(byte deviceId, int ms) {
	MrlServo* servo = (MrlServo*) getDevice(deviceId);
	servo->servoWriteMicroseconds(ms);
}

void MrlComm::setDebug(bool enabled) {
	msg->debug = enabled;
}

void MrlComm::setSerialRate(long rate) {
	msg->publishDebug("setSerialRate " + String(rate));
}

// TODO - implement
// > setTrigger/pin/value
void MrlComm::setTrigger(byte pin, byte triggerValue) {
	msg->publishDebug("implement me ! setDebounce (" + String(pin) + "," + String(triggerValue));
}

// TODO - implement
// > setDebounce/pin/delay
void MrlComm::setDebounce(byte pin, byte delay) {
	msg->publishDebug("implement me ! setDebounce (" + String(pin) + "," + String(delay));
}

// TODO - implement
// > serialAttach/deviceId/relayPin
void MrlComm::serialAttach(byte deviceId, byte relayPin) {

}

// TODO - implement
// > serialRelay/deviceId/[] data
void MrlComm::serialRelay(byte deviceId, byte dataSize, const byte*data) {

}

// > softReset
void MrlComm::softReset() {
	// removing devices & pins
	while (deviceList.size() > 0) {
		delete deviceList.pop();
	}

	while (pinList.size() > 0) {
		delete pinList.pop();
	}

	//resetting variables to default
	loopCount = 0;
	publishBoardStatusModulus = 10000;
	boardStatusEnabled = false;
	msg->debug = false;
	heartbeatEnabled = false;
	lastHeartbeatUpdate = 0;
	for (unsigned int i = 0; i < MAX_MSG_SIZE; i++) {
		customMsgBuffer[i] = 0;
	}
	customMsgSize = 0;
}

// > ultrasonicSensorAttach/deviceId/triggerPin/echoPin
void MrlComm::ultrasonicSensorAttach(byte deviceId, byte triggerPin, byte echoPin) {
	MrlUltrasonicSensor* sensor = (MrlUltrasonicSensor*) addDevice(new MrlUltrasonicSensor(deviceId));
	sensor->attach(triggerPin, echoPin);
}
// > ultrasonicSensorStartRanging/deviceId
void MrlComm::ultrasonicSensorStartRanging(byte deviceId, long timeout) {
	MrlUltrasonicSensor* sensor = (MrlUltrasonicSensor*)getDevice(deviceId);
	sensor->startRanging(timeout);
}
// > ultrasonicSensorStopRanging/deviceId
void MrlComm::ultrasonicSensorStopRanging(byte deviceId) {
	MrlUltrasonicSensor* sensor = (MrlUltrasonicSensor*)getDevice(deviceId);
	sensor->stopRanging();
}

    Contact GitHub API Training Shop Blog About 

    © 2017 GitHub, Inc. Terms Privacy Security Status Help 


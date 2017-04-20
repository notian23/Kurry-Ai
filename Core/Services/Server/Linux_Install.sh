@echo off
# This script uses pip to install dependecies as well as ubuntu
sudo apt install mysql-server
mysql_secure_installation
sudo pip3 install pymysql
sudo apt install apache2
# Arch Linux
# sudo pacman -S mysql-workbench # https://www.archlinux.org/packages/community/x86_64/mysql-workbench/
# sudo pacman -S mysql-python # https://www.archlinux.org/packages/extra/x86_64/mysql-python/
# mysql_secure_installation
# sudo pacman -S apache # https://www.archlinux.org/packages/extra/x86_64/apache/
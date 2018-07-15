#!/bin/bash

echo 'Installing RTL8812 Drivers'

git clone https://github.com/gnab/rtl8812au.git
cd rtl8812au/

#NEED TO CHANGE MAKEFILE OPTIONS

sudo chmod +x install.sh
sudo ./install.sh
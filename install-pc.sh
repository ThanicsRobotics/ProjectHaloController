#!/bin/bash

echo ""
echo "Installer for Qt Pi development environment on PC"
echo ""

read -p "Enter Raspberry Pi IP Address: " address
read -p "Enter directory that contains sysroot: " sysdir
cd $sysdir
if [ -d sysroot ]; then
    rsync -avz pi@$address:/lib sysroot
    rsync -avz pi@$address:/usr/include sysroot/usr
    rsync -avz pi@$address:/usr/lib sysroot/usr
    rsync -avz pi@$address:/opt/vc sysroot/opt
    ./sysroot-relativelinks.py sysroot
    rsync -avz qt5pi pi@$address:/usr/local
else
    echo "cd into raspi directory that contains sysroot"
fi


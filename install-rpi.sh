#!/bin/bash

echo ""
echo "Installer for Thanics Controller dependencies"
echo ""

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo "script at: $DIR"
cd $HOME
mkdir temp
cd temp

# if grep -Fxq "network=" /etc/wpa_supplicant/wpa_supplicant.conf
# then
#     echo "Wifi Network already set up"
# else
#     read -p "Wifi Network SSID: " ssid
#     read -p "Password: " psk

#     echo 'network={
#             ssid='"\"$ssid\""'
#             psk='"\"$psk\""'
#             }' | sudo tee --append /etc/wpa_supplicant/wpa_supplicant.conf
# fi

echo "Updating"
sudo apt-get update -y

if [ -e "/usr/local/lib/libpigpio.so" ]; then
    echo "PIGPIO already installed"
else
    echo ""
    echo "Downloading and installing PIGPIO"
    echo ""
    wget abyz.me.uk/rpi/pigpio/pigpio.zip
    unzip pigpio.zip
    cd PIGPIO
    make -j4
    sudo make install
    cd ..
fi

if [ -e "/usr/local/lib/libusb-0.1.so.4" ]; then
    echo "libusb already installed"
else
    echo ""
    echo "Installing legacy libusb (needed by libptp)"
    echo ""
    wget https://sourceforge.net/projects/libusb/files/libusb-0.1%20%28LEGACY%29/0.1.12/libusb-0.1.12.tar.gz
    tar xzvf libusb-0.1.12.tar.gz
    cd libusb-0.1.12/
    ./configure
    make -j4
    sudo make install
fi

if [ -d "/usr/local/include/boost" ]; then
    echo "Boost already installed"
else
    echo ""
    echo "Downloading and installing Boost"
    echo ""
    wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.gz
    tar -xvf boost_1_67_0.tar.gz
    cd boost_1_67_0
    sudo ./bootstrap.sh
    sudo ./b2 install
    cd ..
    rm -rf boost*
fi

if [ -e "/usr/local/lib/libwiringPi.so" ]; then
    echo "wiringPi already installed"
else
    echo ""
    echo "Downloading and installing wiringPi"
    echo ""
    git clone git://git.drogon.net/wiringPi
    cd wiringPi
    sudo ./build
    cd ..
fi

if [ -e "/usr/local/gcc-8.1.0/bin/g++-8.1.0" ]; then
    echo "GCC version 8 already installed"
else
    echo ""
    echo "Installing GCC version 8"
    echo ""
    git clone https://bitbucket.org/sol_prog/raspberry-pi-gcc-binary.git
    cd raspberry-pi-gcc-binary
    tar xf gcc-8.1.0.tar.bz2
    sudo mv gcc-8.1.0 /usr/local
    echo 'PATH=/usr/local/gcc-8.1.0/bin:$PATH' >> /etc/profile.d/setenvvars.sh
    cd ..
    echo "Replacing old libstdc++ with new one from GCC 8"
    sudo rm /usr/lib/arm-linux-gnueabihf/libstdc++*
    sudo cp /usr/local/gcc-8.1.0/lib/libstdc++.so.6 /usr/lib/arm-linux-gnueabihf/
fi

if [ -e "/usr/bin/gst-launch-1.0" ]; then
    echo "libgstreamer already installed"
else
    echo ""
    echo "Installing libgstreamer"
    echo ""
    sudo apt-get install -y apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools
fi

read -p "Change hostname? (y/n): " choice
if [ $choice == 'y' ]; then
    if grep -Fxq "thanics-controller" /etc/hostname
    then
        echo 'hostname already set'
    else
        echo "Changing hostname to thanics-controller"
        sudo sed -i '1s/.*/thanics-controller/' /etc/hostname
    fi
fi

#add raspi-config automation later...

cd $HOME
sudo rm -rf temp

read -p "You need to reboot to make changes, reboot now? (y/n): " choice
if [ $choice == 'y' ]; then
    sudo reboot
fi
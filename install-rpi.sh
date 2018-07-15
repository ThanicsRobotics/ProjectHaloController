#!/bin/bash

echo ""
echo "Installer for Thanics Controller dependencies Part 1"
echo ""

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo "script at: $DIR"
cd $HOME
mkdir temp
cd temp

if grep -Fxq "network=" /etc/wpa_supplicant/wpa_supplicant.conf
then
    echo "Wifi Network already set up"
else
    read -p "Wifi Network SSID: " ssid
    read -p "Password: " psk

    echo 'network={
            ssid='"\"$ssid\""'
            psk='"\"$psk\""'
            }' | sudo tee --append /etc/wpa_supplicant/wpa_supplicant.conf
fi

git clone https://github.com/al177/esp8089.git
cd esp8089
make -j4
sudo make install

if grep -Fxq "#deb-src" /etc/apt/sources.list
then
    sudo sed -i -e 's/#deb-src/deb-src/g' /etc/apt/sources.list
else
    echo "deb-src already uncommented"
fi



echo "Updating"
sudo apt-get update -y

echo "Installing Qt dependencies"
sudo apt-get build-dep -y qt4-x11
sudo apt-get build-dep -y libqt5gui5
sudo apt-get install -y libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0

sudo mkdir /usr/local/qt5pi
sudo chown pi:pi /usr/local/qt5pi

if grep -Fxq "QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS" /etc/environment
then
    echo "Touchscreen paths already set"
else
    echo 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/vc/lib
    QT_QPA_FONTDIR=/usr/share/fonts/truetype/dejavu/
    QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/event0:rotate=270' | sudo tee --append /etc/environment
fi

if grep -Fxq "Option \"TransformationMatrix\" \"0 1 0 -1 0 1 0 0 1\"" /etc/X11/xorg.conf.d/99-calibration.conf
then
    echo "Touchscreen calibration already set up"
else
    if [ -d "/etc/X11/xorg.conf.d/" ]; then
        echo "xorg.conf.d already exists"
    else
        sudo mkdir /etc/X11/xorg.conf.d/
    fi
    if [ -e "/etc/X11/xorg.conf.d/99-calibration.conf" ]; then
        echo "Replacing touchscreen calibration: /etc/X11/xorg.conf.d/99-calibration.conf"
        sudo rm /etc/X11/xorg.conf.d/99-calibration.conf
    fi

    sudo touch /etc/X11/xorg.conf.d/99-calibration.conf
    echo 'Section \"InputClass\"
            Identifier      \"calibration\"
            MatchProduct    \"ADS7846 Touchscreen\"
            Option  \"MinX\"  \"62103\"
            Option  \"MaxX\"  \"1075\"
            Option  \"MinY\"  \"3186\"
            Option  \"MaxY\"  \"62894\"
            Option  \"SwapXY\"        \"1\" # unless it was already set to 1
            Option \"TransformationMatrix\" \"0 1 0 -1 0 1 0 0 1\"
    EndSection' | sudo tee --append /etc/X11/xorg.conf.d/99-calibration.conf
fi

if grep -Fxq "dtoverlay=ads7846,keep_vref_on=0,cs=0,penirq=40" /boot/config.txt
then
    echo "Touchscreen config already in config.txt"
else
    echo 'hdmi_force_hotplug=1
    hdmi_drive=2
    hdmi_group=2
    hdmi_mode=87
    hdmi_cvt 480 320 60 6 0 0 0
    dtoverlay=ads7846,keep_vref_on=0,cs=0,penirq=40,penirq_pull=2,speed=10000,swapxy=0,pmax=255,xohms=150,xmin=199,xmax=3999,ymin=199,ymax=3999' | sudo tee --append /boot/config.txt
fi

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

if [ -e "/usr/bin/gst-launch-1.0" ]; then
    echo "libgstreamer already installed"
else
    echo ""
    echo "Installing libgstreamer"
    echo ""
    sudo apt-get install -y apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools
fi

if grep -Fxq "thanics-controller" /etc/hostname
then
    echo 'hostname already set'
else
    echo "Changing hostname to thanics-controller"
    sudo sed -i '1s/.*/thanics-controller/' /etc/hostname
fi

#add raspi-config automation later...

cd $HOME
sudo rm -rf temp

read -p "You need to reboot to make changes, reboot now? (y/n): " choice
if [ $choice == 'y' ]; then
    sudo reboot
fi
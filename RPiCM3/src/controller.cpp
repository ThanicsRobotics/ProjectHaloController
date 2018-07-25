#include <controller.h>
#include <wiringPi.h>

Controller::Controller()
    : radio(WLAN::DeviceType::HOST, "", 5000)
{
    
}

void Controller::loopTest()
{
    while (1) {
        messagePacket msg;
        radio.send(msg);
        delay(100);
    }
}
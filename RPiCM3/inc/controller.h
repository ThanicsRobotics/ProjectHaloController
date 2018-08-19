#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <wlanradio.h>
#include <joysticks.h>
#include <adc.h>
#include <battery.h>
#include <button.h>
#include <powerbutton.h>

#include <memory>

class Controller
{
public:
    Controller(std::shared_ptr<bool> shutdown);
    ~Controller();
    void loopTest();
    void printStatus();

private:
    std::shared_ptr<bool> shutdownIndicator;
    WLANRadio radio;
    std::shared_ptr<ADC> adc;
    Joysticks joysticks;
    channels joystickPositions;
    Battery battery;

    Button leftButton;
    Button rightButton;
    PowerButton powerButton;

    void updateJoysticks() { joysticks.getJoystickChannels(joystickPositions); }
};

#endif
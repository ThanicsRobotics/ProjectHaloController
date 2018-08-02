#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <wlanradio.h>
#include <joysticks.h>
#include <adccontroller.h>

class Controller
{
public:
    Controller();
    void loopTest();

private:
    WLANRadio radio;
    ADCController adcController;
};

#endif
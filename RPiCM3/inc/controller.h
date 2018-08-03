#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <wlanradio.h>
#include <joysticks.h>
#include <adc.h>
#include <battery.h>

class Controller
{
public:
    Controller();
    void loopTest();

private:
    WLANRadio radio;
    // ADCController adcController;
    ADC adc;
    Joysticks joysticks;
    Battery battery;

};

#endif
#ifndef ADCCONTROLLER_H
#define ADCCONTROLLER_H

#include <adc.h>
#include <joysticks.h>
#include <battery.h>

class ADCController
{
public:
    ADCController(Joysticks& joystick, Battery& battery);

private:
    ADC adc;
    Joysticks mJoystick;
    Battery mBattery;
};

#endif
#ifndef BATTERY_H
#define BATTERY_H

#include <adc.h>

class Battery
{
public:
    Battery(ADC& adc);
    int getRemainingCapacity();
    float getVoltage();
    float getChargingCurrent();

private:
    ADC adc;

    float parseToVolts(int adcPointValue);
};

#endif
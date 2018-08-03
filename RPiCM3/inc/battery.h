#ifndef BATTERY_H
#define BATTERY_H

#include <adc.h>

class Battery
{
public:
    Battery(ADC& adc);
    bool isCharging() const { return charging; }
    int getRemainingCapacity(int averagingRepetitions);
    float getVoltage(int averagingRepetitions);
    float getChargingCurrent(int averagingRepetitions);

private:
    ADC adc;
    bool charging = false;

    float parseToVolts(int adcPointValue);
};

#endif
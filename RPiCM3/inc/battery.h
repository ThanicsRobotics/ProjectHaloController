#ifndef BATTERY_H
#define BATTERY_H

#include <adc.h>
#include <memory>

class Battery
{
public:
    Battery(std::shared_ptr<ADC> adc);
    bool isCharging() const { return charging; }
    int getRemainingCapacity(int averagingRepetitions);
    float getVoltage(int averagingRepetitions);
    float getChargingCurrent(int averagingRepetitions);

private:
    std::shared_ptr<ADC> adc;
    bool charging = false;

    float parseToVolts(int adcPointValue);
};

#endif
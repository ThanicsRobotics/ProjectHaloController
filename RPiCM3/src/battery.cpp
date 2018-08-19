#include <battery.h>
#include <util.h>

Battery::Battery(std::shared_ptr<ADC> adc)
    : adc(adc)
{

}

int map(float x, float in_min, float in_max, int out_min, int out_max)
{
    return (x - in_min) * (float)(out_max - out_min) / (float)(in_max - in_min) + out_min;
}

// returns 0-100 for 0% to 100% capacity
int Battery::getRemainingCapacity(int averagingRepetitions)
{
    float voltage = getVoltage(averagingRepetitions);
    if (voltage > 4.18) return 100;
    else if (voltage < 3.4) return 0;
    else return map(voltage, 3.4, 4.18, 0, 100);
}

float Battery::parseToVolts(int adcPointValue)
{
    return 3.3 * ((float)adcPointValue / 1024.0);
}

float Battery::getChargingCurrent(int averagingRepetitions)
{
    // 1V on ADC = 1A of charging current
    const float offset = 0.067; // voltage reads this when not charging
    float sum = 0.0;
    for (int i = 0; i < averagingRepetitions; i++)
    {
        sum += parseToVolts(adc->getChannelValue(6));
    }
    float chargeCurrent = ((sum / averagingRepetitions) - offset) * 1000; // convert to mA, subtract offset

    // Deadband
    if (chargeCurrent > 30)
    {
        charging = true;
        return chargeCurrent;
    }
    else
    {
        charging = false;
        return 0;
    }
}

float Battery::getVoltage(int averagingRepetitions)
{
    float sum = 0.0;
    for (int i = 0; i < averagingRepetitions; i++)
    {
        sum += parseToVolts(adc->getChannelValue(0));
    }

    // Battery reading goes through divide-by-2 resistor divider, 
    // so we multiply by 2 to normalize
    return (sum / averagingRepetitions) * 2;
}
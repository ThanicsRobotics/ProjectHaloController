#include <battery.h>

Battery::Battery(ADC& adc)
    : adc(adc)
{

}

int map(float x, float in_min, float in_max, int out_min, int out_max)
{
    return (x - in_min) * (float)(out_max - out_min) / (float)(in_max - in_min) + out_min;
}

// returns 0-100 for 0% to 100% capacity
int Battery::getRemainingCapacity()
{
    float voltage = getVoltage();
    if (voltage > 4.18) return 100;
    else if (voltage < 3.4) return 0;
    else return map(voltage, 3.4, 4.18, 0, 100);
}

float Battery::parseToVolts(int adcPointValue)
{
    return 3.3 * ((float)adcPointValue / 1024.0);
}

float Battery::getChargingCurrent()
{
    // 1V on ADC = 1A of charging current
    int adcPointValue = adc.getChannelValue(6);

    return parseToVolts(adcPointValue);
}

float Battery::getVoltage()
{
    int adcPointValue = adc.getChannelValue(0);

    // Battery reading goes through divide-by-2 resistor divider, 
    // so we multiply by 2 to normalize
    return parseToVolts(adcPointValue) * 2;
}
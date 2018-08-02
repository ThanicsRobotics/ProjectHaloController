#ifndef ADCCONTROLLER_H
#define ADCCONTROLLER_H

#include <adc.h>
#include <joysticks.h>
#include <battery.h>
#include <types.h>

#include <string>
#include <functional>

class ADCController
{
public:
    ADCController();
    void getJoystickPositions(channels& joystickPositions);
    bool isLeftButtonPressed() { return mJoystick.isLeftButtonPressed(); }
    bool isRightButtonPressed() { return mJoystick.isRightButtonPressed(); }

    int getBatteryLife() { return averageInts([this] { return mBattery.getRemainingCapacity(); }, 10); }
    float getBatteryVoltage() { return averageFloats([this] { return mBattery.getVoltage(); }, 10); }
    float getChargeCurrent() { return averageFloats([this] { return mBattery.getChargingCurrent(); }, 10); }

private:
    ADC adc;
    Joysticks mJoystick;
    Battery mBattery;

    float averageFloats(std::function<float()> function, int repetitions);
    int averageInts(std::function<int()> function, int repetitions);
};

#endif
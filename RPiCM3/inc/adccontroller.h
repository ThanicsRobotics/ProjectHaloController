#ifndef ADCCONTROLLER_H
#define ADCCONTROLLER_H

#include <adc.h>
#include <joysticks.h>
#include <battery.h>
#include <types.h>

#include <string>

class ADCController
{
public:
    ADCController();
    void getJoystickPositions(channels& joystickPositions);
    bool isLeftButtonPressed() { return mJoystick.isLeftButtonPressed(); }
    bool isRightButtonPressed() { return mJoystick.isRightButtonPressed(); }

    int getBatteryLife() { return mBattery.getRemainingCapacity(); }
    float getBatteryVoltage() { return mBattery.getVoltage(); }
    float getChargeCurrent() { return mBattery.getChargingCurrent(); }

private:
    ADC adc;
    Joysticks mJoystick;
    Battery mBattery;
};

#endif
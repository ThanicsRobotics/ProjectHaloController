#include <adccontroller.h>

ADCController::ADCController()
    : mJoystick(adc), mBattery(adc)
{
    
}

void ADCController::getJoystickPositions(channels& joystickPositions)
{
    channels rcChannels;
    mJoystick.getJoystickChannels(rcChannels);
    joystickPositions = rcChannels;
}
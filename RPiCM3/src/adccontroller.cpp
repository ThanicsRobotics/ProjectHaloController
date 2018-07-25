#include <adccontroller.h>

ADCController::ADCController(Joysticks& joystick, Battery& battery)
    : mJoystick(joystick), mBattery(battery)
{
    
}
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

float ADCController::averageFloats(std::function<float()> function, int repetitions)
{
    float sum = 0.0;
    for (int i = 0; i < repetitions; i++)
    {
        sum += function();
    }
    return sum / repetitions;
}

int ADCController::averageInts(std::function<int()> function, int repetitions)
{
    int sum = 0;
    for (int i = 0; i < repetitions; i++)
    {
        sum += function();
    }
    return sum / repetitions;
}
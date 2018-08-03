#include <joysticks.h>
#include <wiringPi.h>
#include <iostream>

Joysticks::Joysticks(ADC& adc)
    : adc(adc)
{
    pinMode(38, INPUT);
    pinMode(41, INPUT);
}

uint16_t reverseChannel(uint16_t originalPWM)
{
    return 3000 - originalPWM;
}

void Joysticks::getJoystickChannels(channels& rcChannels) {
    std::array<uint16_t, 7> totalAdcData{};
    
    const int repetitions = 3;
    for (int i = 0; i < repetitions; i++)
    {
        std::array<uint16_t, 7> rawADCPoints;
        adc.getADCData(rawADCPoints);
        for (int j = 0; j < 7; j++)
        {
            totalAdcData[j] += rawADCPoints[j];
        }
    }

    rcChannels.pitchPWM = reverseChannel(pointsToPWM(totalAdcData[4]/repetitions));
    rcChannels.rollPWM = reverseChannel(pointsToPWM(totalAdcData[3]/repetitions));
    rcChannels.yawPWM = reverseChannel(pointsToPWM(totalAdcData[1]/repetitions));
    rcChannels.throttlePWM = reverseChannel(pointsToPWM(totalAdcData[2]/repetitions));
    // std::cout << "pitch: " << rcChannels.pitchPWM
    //           << "\nroll: " << rcChannels.rollPWM
    //           << "\nyaw: " << rcChannels.yawPWM
    //           << "\nthrottle: " << rcChannels.throttlePWM
    std::cout << "time: " << millis() - lastTime
              << "\n-----" << std::endl;
    lastTime = millis();
}

uint16_t Joysticks::pointsToPWM(uint16_t points) {
    return (points * 1000 / 1024) + 1000;
}

bool Joysticks::isLeftButtonPressed()
{
    return digitalRead(38) ? true : false;
}

bool Joysticks::isRightButtonPressed()
{
    return digitalRead(41) ? true : false;
}
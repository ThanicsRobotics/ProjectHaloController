#include <joysticks.h>
#include <wiringPi.h>
#include <iostream>

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

    rcChannels.pitchPWM = pointsToPWM(totalAdcData[4]/repetitions);
    rcChannels.rollPWM = pointsToPWM(totalAdcData[3]/repetitions);
    rcChannels.yawPWM = pointsToPWM(totalAdcData[1]/repetitions);
    rcChannels.throttlePWM = pointsToPWM(totalAdcData[2]/repetitions);
    std::cout << "pitch: " << rcChannels.pitchPWM
              << "\nroll: " << rcChannels.rollPWM
              << "\nyaw: " << rcChannels.yawPWM
              << "\nthrottle: " << rcChannels.throttlePWM
              << "\ntime: " << millis() - lastTime
              << "\n-----" << std::endl;
    lastTime = millis();
}

float Joysticks::pointsToVolts(uint16_t points) {
    return (points/1024)*3.3;
}

uint16_t Joysticks::pointsToPWM(uint16_t points) {
    return (points * 1000 / 1024) + 1000;
}
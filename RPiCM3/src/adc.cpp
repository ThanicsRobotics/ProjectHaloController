#include <adc.h>

#if RPI_COMPILE
#include <pigpio.h>

#define ADC_ADDR 0x33

void ADC::parseToPoints(uint8_t data[14], std::array<uint16_t, 7>& pointValues) {
    //Data comes out from ADC as two bytes:
    // 111111xx xxxxxxxx
    //x's represent 10-bit number
    for(int i = 0; i < 14; i += 2) {
        data[i] &= 0b00000011;
        pointValues[i/2] = (data[i] << 8) | data[i+1];
        //std::cout << "rV:\n" << rawValues[i/2] << std::endl;
    }
}

float ADC::pointsToVolts(uint16_t points) {
    return (points/1024)*3.3;
}

uint16_t ADC::pointsToPWM(uint16_t points) {
    return (points * 1000 / 1024) + 1000;
}

void ADC::setupADC() {
    adcFd = i2cOpen(1,ADC_ADDR,0);
    i2cWriteByte(adcFd, 0x82); //Setup Byte: 10000010

}

void ADC::closeADC() {
    std::cout << "Closing ADC\n";
    i2cClose(adcFd);
}

void ADC::getADCData(std::array<uint16_t, 7>& pointArray) {
    uint8_t adcValues[14];
    i2cReadI2CBlockData(adcFd,0x0D,(char*)adcValues,14); // Config Byte: 00001101
    //for (int i = 0; i < sizeof(adcValues); i ++) std::cout << (int)adcValues[i] << std::endl;

    parseToPoints(adcValues, pointArray);
}

void ADC::getJoystickChannels(channels& rcChannels) {
    static int lastTime = millis();
    std::array<uint16_t, 7> totalAdcData;
    std::fill(totalAdcData.begin(), totalAdcData.end(), 0);
    const int repetitions = 3;
    for (int i = 0; i < repetitions; i++)
    {
        std::array<uint16_t, 7> rawADCPoints;
        getADCData(rawADCPoints);
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

#endif


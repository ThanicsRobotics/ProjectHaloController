#include <adc.h>

#include <pigpio.h>
#include <wiringPi.h>
#include <iostream>

#define ADC_ADDR 0x33

void ADC::setupADC() {
    adcFd = i2cOpen(1,ADC_ADDR,0);
    i2cWriteByte(adcFd, 0x82); //Setup Byte: 10000010

}

void ADC::closeADC() {
    std::cout << "Closing ADC\n";
    i2cClose(adcFd);
}

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

void ADC::getADCData(std::array<uint16_t, 7>& pointArray) {
    uint8_t adcValues[14];
    i2cReadI2CBlockData(adcFd,0x0D,(char*)adcValues,14); // Config Byte: 00001101
    //for (int i = 0; i < sizeof(adcValues); i ++) std::cout << (int)adcValues[i] << std::endl;

    parseToPoints(adcValues, pointArray);
}
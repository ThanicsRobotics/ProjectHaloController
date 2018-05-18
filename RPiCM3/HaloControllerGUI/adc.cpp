#include <adc.h>

#if RPI_COMPILE
#include <pigpio.h>

#define ADC_ADDR 0x33

//int rawValues[6];
//char adcValues[12];
int adcFd;

const uint16_t* parseToPoints(uint8_t data[14]) {
    static uint16_t rawValues[7];
    //Data comes out from ADC as two bytes:
    // 111111xx xxxxxxxx
    //x's represent 10-bit number
    for(int i = 0; i < sizeof(data); i+= 2) {
        data[i] &= 0b00000011;
        rawValues[i/2] = ((data[i] << 8) & 0xFF00) | (data[i+1] & 0xFF);
    }
    return rawValues;
}

float pointsToVolts(uint16_t points) {
    return (points/1024)*3.3;
}

uint16_t pointsToPWM(uint16_t points) {
    printf("here2.5\n");
    return (points * 1000 / 1024) + 1000;
}

void setupADC() {
    adcFd = i2cOpen(1,ADC_ADDR,0);
    i2cWriteByte(adcFd, 0x82); //Setup Byte: 10000010

}

void closeADC() {
    i2cClose(adcFd);
}

const uint16_t* getADCData() {
    uint8_t adcValues[14];
    i2cReadI2CBlockData(adcFd,0x0D,(char*)adcValues,14); // Config Byte: 00001101
    for (int i = 0; i < sizeof(adcValues); i ++) std::cout << (int)adcValues[i] << std::endl;
    return parseToPoints(adcValues);
}

const channels& getJoystickChannels() {
    //printf("here\n");
    static channels joystickChannels;
    const uint16_t *rawADCPoints = getADCData();
    //printf("here2\n");
    //std::cout << rawADCPoints << std::endl;
    joystickChannels.pitchPWM = 1000 + pointsToPWM(rawADCPoints[0]);
    joystickChannels.rollPWM = 1000 + pointsToPWM(rawADCPoints[1]);
    joystickChannels.yawPWM = 1000 + pointsToPWM(rawADCPoints[2]);
    joystickChannels.throttlePWM = 1000 + pointsToPWM(rawADCPoints[3]);
    //printf("here3\n");
    return joystickChannels;
}

#endif


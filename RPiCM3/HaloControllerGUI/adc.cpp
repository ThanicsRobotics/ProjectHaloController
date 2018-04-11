#include <adc.h>

#if RPI_COMPILE
#include <pigpio.h>

#define ADC_ADDR 0x33

int rawValues[6];
char *adcValues[12];
int adcFd;

void parseToPoints(char data[12]) {
    for(int i = 0; i < sizeof(data); i+= 2) {
        data[i] -= 252;
        if (i > 0) rawValues[i/2] = data[i-1] << 8 | data[i];
    }
}

float pointsToVolts(int points) {
    return (points/1024)*3.3;
}

int pointsToPWM(int points) {
    return (points * 1000 / 1024) + 1000;
}

void setupADC() {
    adcFd = i2cOpen(1,ADC_ADDR,0);
}

void getADCData() {
    i2cReadI2CBlockData(adcFd,0x0B,adcValues,12);
}
#endif


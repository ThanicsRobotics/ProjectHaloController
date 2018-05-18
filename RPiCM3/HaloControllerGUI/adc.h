#ifndef ADC_H
#define ADC_H
#define RPI_COMPILE 1

#include <radio.h>

#if RPI_COMPILE
const uint16_t* parseToPoints(uint8_t data[14]);
float pointsToVolts(uint16_t points);
uint16_t pointsToPWM(uint16_t points);

void setupADC();
const uint16_t *getADCData();
const channels& getJoystickChannels();
void closeADC();

#endif

#endif // ADC_H

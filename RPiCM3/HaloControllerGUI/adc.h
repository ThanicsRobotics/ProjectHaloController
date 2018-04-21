#ifndef ADC_H
#define ADC_H
#define RPI_COMPILE 1

#if RPI_COMPILE
int *parseToPoints(char data[12]);
float pointsToVolts(int points);
int pointsToPWM(int points);

void setupADC();
int *getADCData();
#endif

#endif // ADC_H

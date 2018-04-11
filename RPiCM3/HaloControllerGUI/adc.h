#ifndef ADC_H
#define ADC_H
#define RPI_COMPILE 0

#if RPI_COMPILE
void parseToPoints(char data[12]);
float pointsToVolts(int points);
int pointsToPWM(int points);


void setupADC();
void getADCData();
#endif

#endif // ADC_H

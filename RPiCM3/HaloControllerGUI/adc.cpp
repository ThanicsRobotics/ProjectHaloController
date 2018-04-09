#include <wiringPi.h>

int rawValues[6];

void parse(char data[12]) {
    for(int i = 0; i < sizeof(data); i+= 2) {
        data[i] -= 252;
        if (i > 0) rawValues[i/2] = data[i-1] << 8 | data[i];
    }
}

float pointsToVolts(int points) {
    return (points/1024)*3.3;
}



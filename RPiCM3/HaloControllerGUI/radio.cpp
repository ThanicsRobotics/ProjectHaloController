#include <radio.h>
#include <adc.h>

#if RPI_COMPILE
#include <pigpio.h>

int radioFd;

void setupRadio() {
    radioFd = serOpen("/dev/ttyAMA0", 9600, 0);
}

void radioSend() {
    int data[6] = getADCData();
    int pwm[4];
    for (int i = 0; i < 3; i++) {
        pwm[i] = pointsToPWM(data[i]);
    }
    int yaw = pwm[0];
    int altitude = pwm[1];
    int roll = pwm[2];
    int pitch = pwm[3];

    //MAVLink stuff

    serWrite(radioFd, )
}
#endif

#include <radio.h>
#include <adc.h>

#if RPI_COMPILE
#include <pigpio.h>

int radioFd;

void setupRadio() {
    radioFd = serOpen("/dev/ttyAMA0", 9600, 0);
}

void mavlinkSend() {
    int data[6] = getADCData();
    int pwm[4];
    for (int i = 0; i < 3; i++) {
        pwm[i] = pointsToPWM(data[i]);
    }
    int yaw = pwm[0];
    int altitude = pwm[1];
    int roll = pwm[2];
    int pitch = pwm[3];


}

void mavlinkReceive() {
    mavlink_message_t msg;
    mavlink_status_t status;
    while (serDataAvailable(radioFd)) {
        uint8_t data = serReadByte(radioFd);
        if(mavlink_parse_char(MAVLINK_COMM_0, data, &msg, &status)) {
            switch(msg.msgid) {
                case MAVLINK_MSG_ID_HEARTBEAT:
                    mavlink_heartbeat_t hb;
                    mavlink_msg_heartbeat_decode(&msg, &hb);
                    break;
            }
        }
    }
#endif

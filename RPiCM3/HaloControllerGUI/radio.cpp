#include <radio.h>
#include <adc.h>

#if RPI_COMPILE
#include <pigpio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define PORT "9999"

int radioFd;

void setupRadio() {
    radioFd = serOpen("/dev/ttyAMA0", 9600, 0);
}

//void telemetryStream() {
//    char server_message[256] = "You have reached server!";

//    int server_socket;
//    server_socket = socket(AF_INET, SOCK_STREAM, 0);
//    struct sockaddr_in server_address;
//    server_address.sin_family = AF_INET;
//    server_address.sin_port = htons(9002);
//    server_address.sin_addr.s_addr = INADDR_ANY;

//    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
//    listen(server_socket, 5);
//    int client_socket;
//    client_socket = accept(server_socket, NULL, NULL);
//    send(client_socket, server_message, sizeof(server_message), 0);
//    close(server_socket);
//}

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

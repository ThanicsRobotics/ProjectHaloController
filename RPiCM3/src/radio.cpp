#include <radio.h>
#include <adc.h>
#include <mavlink/common/mavlink.h>

#if RPI_COMPILE
#include <pigpio.h>
#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define PORT "9999"
#define SYSID 255
#define COMPID 1

int droneStatus;

buffer sendHeartbeat(uint8_t mode, uint8_t status) {
    mavlink_message_t msg;
    uint16_t len;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_heartbeat_pack(SYSID, COMPID, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, mode, 0, status);
    len = mavlink_msg_to_send_buffer(buf, &msg);

    buffer sendBuffer;
    sendBuffer.buf = (std::shared_ptr<uint8_t[]>)buf;
    sendBuffer.len = len;
    return sendBuffer;
}

buffer sendRCChannels(uint16_t pitch, uint16_t roll, uint16_t yaw, uint16_t throttle) {
    mavlink_message_t msg;
    uint16_t len;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_rc_channels_pack(SYSID, COMPID, &msg, millis(), 4, pitch, roll, yaw, throttle,
        UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX,
        UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, 255);
    len = mavlink_msg_to_send_buffer(buf, &msg);

    buffer sendBuffer;
    sendBuffer.buf = (std::shared_ptr<uint8_t[]>)buf;
    sendBuffer.len = len;
    return sendBuffer;
}

void mavlinkReceivePacket(uint8_t *packet) {
    uint8_t byte = 0;
    int i = 0;
    while (byte != '\0') {
        byte = packet[i];
        printf("byte %d: %d\n", i, byte);
        mavlinkReceiveByte(packet[i]);
        i += 1;
    }
}

void mavlinkReceiveByte(uint8_t data) {
    printf("byte: %d\n", data);
    mavlink_message_t msg;
    mavlink_status_t status;
    if(mavlink_parse_char(MAVLINK_COMM_0, data, &msg, &status)) {
        printf("Received message with ID %d, sequence: %d from component %d of system %d\n",
        msg.msgid, msg.seq, msg.compid, msg.sysid);
        switch(msg.msgid) {
            case MAVLINK_MSG_ID_HEARTBEAT:
                mavlink_heartbeat_t hb;
                mavlink_msg_heartbeat_decode(&msg, &hb);
                droneStatus = hb.system_status;
                break;

            case MAVLINK_MSG_ID_COMMAND_LONG:
                mavlink_command_long_t command;
//                switch (command.command) {

//                }
                break;
            default:
                break;
        }
    }
}

#endif

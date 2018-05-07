#include <radio.h>
#include <adc.h>
#include <mavlink/common/mavlink.h>

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
#define SYSID 255
#define COMPID 1

int droneStatus;

buffer sendHeartbeat(uint8_t mode, uint8_t status) {
    mavlink_message_t msg;
    uint16_t len;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_heartbeat_pack(SYSID, COMPID, &msg, MAV_TYPE_GCS, MAV_AUTOPILOT_GENERIC, mode, 0, status);
    len = mavlink_msg_to_send_buffer(buf, &msg);
    printf("%d bytes\n", len);

    buffer sendBuffer;
    sendBuffer.buf = buf;
    sendBuffer.len = len;
    return sendBuffer;
}

void mavlinkReceivePacket(char *packet) {
    uint8_t byte = 0;
    int i = 0;
    while (byte != '\0') {
        byte = packet[i];
        mavlinkReceiveByte((uint8_t)packet[i]);
        i += 1;
    }
}

void mavlinkReceiveByte(uint8_t data) {
    mavlink_message_t msg;
    mavlink_status_t status;
    if(mavlink_parse_char(MAVLINK_COMM_0, data, &msg, &status)) {
        printf("Received message with ID %d, sequence: %d from component %d of system %d\n",
        msg.msgid, msg.seq, msg.compid, msg.sysid);
//        switch(msg.msgid) {
//            case MAVLINK_MSG_ID_HEARTBEAT:
//                mavlink_heartbeat_t hb;
//                mavlink_msg_heartbeat_decode(&msg, &hb);
//                droneStatus = hb.system_status;

//                break;

//            case MAVLINK_MSG_ID_COMMAND_LONG:
//                mavlink_command_long_t command;
//                switch (command.command) {
//                    case MAV_CMD_NAV_LAND:
//                        break;
//                    case MAV_CMD_NAV_TAKEOFF:
//                        break;
//                }
//                break;
//            default:
//                break;
//        }
    }
}

#endif

#ifndef RADIO_H
#define RADIO_H

#include <stdint.h>

struct buffer
{
    uint8_t *buf;
    uint16_t len;
};

buffer sendHeartbeat(uint8_t mode, uint8_t status);
void mavlinkReceivePacket(char *packet);
void mavlinkReceiveByte(uint8_t data);


#endif // RADIO_H

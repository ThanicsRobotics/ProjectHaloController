#ifndef RADIO_H
#define RADIO_H

#include <stdint.h>

uint8_t *sendHeartbeat(uint8_t mode, uint8_t status);
void mavlinkReceivePacket(char *packet);
void mavlinkReceiveByte(uint8_t data);

#endif // RADIO_H

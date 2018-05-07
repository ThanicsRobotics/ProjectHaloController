#ifndef STREAM_H
#define STREAM_H

#include <stdint.h>

class Stream
{
public:
    Stream(char *ip_address, char *port);
    int sendData(uint8_t *data, uint16_t len);
    char *receiveDataPacket();
    void closeStream();
};

#endif // STREAM_H

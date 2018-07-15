#include <serial.h>

#include <pigpio.h>
#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

Serial::Serial() {
    serialConfigured = false;
}

void Serial::setupSerial(char* port, int baud) {
    if ((serialFd = serOpen(port, baud, 0)) < 0) {
        std::cout << "Unable to open serial interface: " << strerror(errno) << '\n';
        fflush(stdout);
    }
    else {
        std::cout << "Opening Serial. FD: " << serialFd << " ID: " << pthread_self() << '\n';
        serialConfigured = true;
    }
}

void Serial::closeSerial() {
    std::cout << "Closing Serial\n";
    if (serialConfigured) serClose(serialFd);
}

void Serial::startSerialLoop() {
    //pthread_t serialThread;
    //pthread_create(&serialThread, NULL, serialLoop, NULL);
}

char *Serial::readLine() {
    if(!serialConfigured) return "\0";
    static char buffer[300];
    memset(buffer, 0, sizeof(buffer));
    int i = 0;
    for (char thisChar = (char)serReadByte(serialFd); thisChar != '\n';
    thisChar = (char)serReadByte(serialFd)) {
        buffer[i] = thisChar;
        i += 1;
    }
    buffer[i] = '\n';
    buffer[i+1] = '\0';
    return buffer;
}

char Serial::readChar() {
    if(!serialConfigured) return NULL;
    int timer = millis();
    while((serDataAvailable(serialFd) < 1) && (millis() - timer < 1));
    if(serDataAvailable(serialFd) > 0) {
        return (char)serReadByte(serialFd);
    }
    else return NULL;
}

int Serial::write(uint8_t* bytes, uint16_t len) {
    int status = 0;
    // for (int i = 0; i < len; i++) {
    //     // if((status = serWriteByte(serialFd, bytes.get()[i])) < 0) {
    //     //     printf("%d\n", status);
    //     //     return status;
    //     // }
    //     printf("byte %d/%d: %d\n", i+1, len, bytes.get()[i]);
    // }
    if((status = serWrite(serialFd, (char*)bytes, len)) < 0) {
        printf("%s\n", strerror(status));
    }
    return status;
}

Serial::~Serial() {
    //pthread_join(serialThread, NULL);
}

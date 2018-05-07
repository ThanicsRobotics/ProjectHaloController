#include <serial.h>

#include <pigpio.h>
#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int serialFd;
bool serialConfigured = false;

Serial::Serial() {

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

//void *Serial::serialLoop(void*) {
//    if(!serialConfigured) this->setupSerial("/dev/serial0", 9600);
//    while(run) {
//        //this->readLine();
//        //delayMicroseconds(500);
//    }
//    return NULL;
//}

//void Serial::startSerialLoop() {
//    pthread_t serialThread;
//    pthread_create(&serialThread, NULL, serialLoop, NULL);
//}

char *Serial::readLine() {
    if(!serialConfigured) return '\0';
    char buffer[300];
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
    if(!serialConfigured) return '\0';
    if(serDataAvailable(serialFd) > 0) {
        return (char)serReadByte(serialFd);
    }
    else return '\0';
}

int Serial::write(uint8_t* bytes, uint16_t len) {
    int status = 0;
    for (int i = 0; i < len; i++) {
        if(status = serWriteByte(serialFd, bytes[i]) < 0) return status;
    }
    return status;
}

Serial::~Serial() {
    pthread_join(serialThread, NULL);
}

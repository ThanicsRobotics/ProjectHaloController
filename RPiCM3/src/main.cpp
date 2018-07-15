#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <thread>

#include <adc.h>
#include <radio.h>
#include <pthread.h>
#include <backendinterface.h>
#include <stream.h>
#include <mavlink/common/mavlink.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <serial.h>
#include <array>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#if RPI_COMPILE
#include <pigpio.h>
#include <wiringPi.h>

#define CONTROLLER_IP "192.168.168.232"

ADC adc;
Radio<Serial> radio;
//Stream stream(CONTROLLER_IP, "9999");

void shutdown(int signum) {
    adc.closeADC();
    radio.closeSerial();
}

void backendLoop() {
    signal(SIGINT, shutdown);

    adc.setupADC();
    radio.setupSerial("/dev/serial0", 115200);
    int timer, rcTimer = millis();

    //Main loop
    std::array<uint8_t, 15> dummyMsg = {0xFF, 0xFE, 0x01, 0x01, 0x00, 0x05, 0xDD, 0x05, 0xDD, 0x05, 0xDD, 0x05, 0xDD, 0xFD, 0xFC};
    uint8_t count = 0;
    while (1) {
//        if(millis() - timer > 1000) {
//            printf("Sending Heartbeat\n");
//            radioBuffer sendBuffer = radio.sendHeartbeat(MAV_MODE_PREFLIGHT, MAV_STATE_STANDBY);
//            radio.write(sendBuffer.buf, sendBuffer.len);
//            timer = millis();
//        }
//        else if (millis() - rcTimer > 100) {
//            radioBuffer buffer = radio.sendRCChannels(getJoystickChannels());
//            radio.write(buffer.buf, buffer.len);
//            rcTimer = millis();
//        }
//        radio.mavlinkReceiveByte(radio.readChar());
        channels rcChannels;
        adc.getJoystickChannels(rcChannels);
        if (count == 255) count = 0;
        dummyMsg[4] = count;
        dummyMsg[5] = (rcChannels.throttlePWM >> 8) & 0xFF;
        dummyMsg[6] = rcChannels.throttlePWM & 0xFF;
        dummyMsg[7] = (rcChannels.pitchPWM >> 8) & 0xFF;
        dummyMsg[8] = rcChannels.pitchPWM & 0xFF;
        dummyMsg[9] = (rcChannels.rollPWM >> 8) & 0xFF;
        dummyMsg[10] = rcChannels.rollPWM & 0xFF;
        dummyMsg[11] = (rcChannels.yawPWM >> 8) & 0xFF;
        dummyMsg[12] = rcChannels.yawPWM & 0xFF;

        //printf("%d\n", dummyMsg[4]);
        radio.write(dummyMsg.data(), 15);
        count++;
        //delay(50);
    }
    //stream.receiveDataPacket();

    //stream.sendData(sendBuffer.buf, sendBuffer.len);
    //printf("sending\n");
    //std::string message = "Hello again";
    //stream.sendData((uint8_t*)message.c_str(), sizeof(message));
    //printf("done\n");
//    for(int i = 0; i < 10; i++) {
//        uint8_t *data;
//        sprintf((char*)data, "%d", i);
//        stream.sendData(data);
//    }
    //stream.receiveDataPacket();
    //mavlinkReceivePacket(stream.receiveDataPacket());
//    while(1) {

//    }

}

#endif

int main(int argc, char *argv[])
{
    #if RPI_COMPILE
    gpioInitialise();
    wiringPiSetupGpio();
    //pthread_t backendThread;
    std::thread backendThread(backendLoop);
    //pthread_create(&backendThread, NULL, backendLoop, NULL);
    #endif

    BackendInterface closing;

    QScopedPointer<BackendInterface> backend(new BackendInterface);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.rootContext()->setContextProperty("backend", backend.data());
    //QObject::connect(&app, SIGNAL(aboutToQuit()), &closing, SLOT(closing.cleanup(stream)));

    return app.exec();
}



//int main(int argc, char *argv[])
//{

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();
//}

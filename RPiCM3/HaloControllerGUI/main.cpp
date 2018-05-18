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

#if RPI_COMPILE
#include <pigpio.h>
#include <wiringPi.h>

#define CONTROLLER_IP "192.168.168.232"

//Stream stream(CONTROLLER_IP, "9999");

void backendLoop(){
    setupADC();
    Radio<Serial> radio;
    radio.setupSerial("/dev/serial0", 9600);
    int timer = millis();

    //Main loop
    while (1) {
        if(millis() - timer > 1000) {
            printf("Sending Heartbeat\n");
            radioBuffer sendBuffer = radio.sendHeartbeat(MAV_MODE_PREFLIGHT, MAV_STATE_STANDBY);
            radio.write(sendBuffer.buf, sendBuffer.len);
            timer = millis();
        }
        //printf("1\n");
        radio.mavlinkReceiveByte(radio.readChar());
        //printf("2\n");
        radioBuffer buffer = radio.sendRCChannels(getJoystickChannels());
        //printf("3\n");
        radio.write(buffer.buf, buffer.len);
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

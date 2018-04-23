#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <adc.h>
#include <radio.h>
#include <pthread.h>
#include <backendinterface.h>
#include <stream.h>
#include <mavlink/common/mavlink.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

#if RPI_COMPILE
#include <pigpio.h>

#define CONTROLLER_IP "192.168.168.232"

Stream stream(CONTROLLER_IP, "9999");

void *backendLoop(void *void_ptr){
    setupADC();
    stream.sendData(sendHeartbeat(MAV_MODE_PREFLIGHT, MAV_STATE_STANDBY));
    for(int i = 0; i < 10; i++) {
        uint8_t *data;
        sprintf((char*)data, "%d", i);
        stream.sendData(data);
    }
    mavlinkReceivePacket(stream.receiveDataPacket());
    while(1) {

    }

    return NULL;
}

#endif

int main(int argc, char *argv[])
{
    #if RPI_COMPILE
    gpioInitialise();
    pthread_t backendThread;
    pthread_create(&backendThread, NULL, backendLoop, NULL);
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
    QObject::connect(&app, SIGNAL(aboutToQuit()), &closing, SLOT(closing.cleanup(stream)));

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

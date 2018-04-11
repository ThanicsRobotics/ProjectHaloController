#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <adc.h>
#include <radio.h>
#include <pthread.h>
#include <backendinterface.h>

#if RPI_COMPILE
void *backendLoop(void *void_ptr){
    setupADC();

    return NULL;
}
#endif

int main(int argc, char *argv[])
{
    #if RPI_COMPILE
    pthread_t backendThread;
    pthread_create(&backendThread, NULL, backendLoop, NULL);
    #endif

    QScopedPointer<BackendInterface> backend(new BackendInterface);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.rootContext()->setContextProperty("backend", backend.data());

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

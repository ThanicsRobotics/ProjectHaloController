#ifndef BACKENDINTERFACE_H
#define BACKENDINTERFACE_H

#include <QObject>
#include <stream.h>

class BackendInterface : public QObject
{
    Q_OBJECT
public:
    explicit BackendInterface(QObject *parent = nullptr);
    Q_INVOKABLE void operateLandingGear(int direction);
    Q_INVOKABLE void takeoff();
    Q_INVOKABLE void land();
signals:

public slots:
    void cleanup(Stream stream);
};

#endif // BACKENDINTERFACE_H

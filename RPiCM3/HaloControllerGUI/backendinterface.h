#ifndef BACKENDINTERFACE_H
#define BACKENDINTERFACE_H

#include <QObject>

class BackendInterface : public QObject
{
    Q_OBJECT
public:
    explicit BackendInterface(QObject *parent = nullptr);
    Q_INVOKABLE void operateLandingGear(int direction);
signals:

public slots:
};

#endif // BACKENDINTERFACE_H

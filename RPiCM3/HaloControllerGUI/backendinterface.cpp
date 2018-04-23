#include "backendinterface.h"
#include "adc.h"
#include "stream.h"

BackendInterface::BackendInterface(QObject *parent) : QObject(parent)
{

}

void BackendInterface::operateLandingGear(int direction)
{

}

void BackendInterface::takeoff()
{

}

void BackendInterface::land()
{

}

void BackendInterface::cleanup(Stream stream)
{
    stream.closeStream();
    closeADC();
}

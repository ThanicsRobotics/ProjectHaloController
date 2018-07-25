#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <wlanradio.h>
#include <joystick.h>

class Controller
{
public:
    Controller();
    void loopTest();

private:
    WLANRadio radio;
    
};

#endif
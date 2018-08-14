#ifndef BUTTON_H
#define BUTTON_H

#include <holdtimer.h>

class Button
{
public:
    Button(int gpioPin);
    bool isPressed() const;

private:
    int pin = -1;
};

#endif
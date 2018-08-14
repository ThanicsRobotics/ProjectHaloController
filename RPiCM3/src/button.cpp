#include <button.h>
#include <wiringPi.h>

Button::Button(int gpioPin)
    : pin(gpioPin)
{
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_DOWN);
}

bool Button::isPressed() const
{
    return digitalRead(pin);
}


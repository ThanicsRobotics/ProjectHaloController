#ifndef POWERBUTTON_H
#define POWERBUTTON_H

#include <button.h>
#include <memory>

class PowerButton
{
public:
    PowerButton(int gpioPin, std::shared_ptr<bool> shutdown);
    void update();
    bool isPressed() const { return button.isPressed(); }

private:
    Button button;
    HoldTimer holdTimer;
    std::shared_ptr<bool> shutdownIndicator;
};

#endif
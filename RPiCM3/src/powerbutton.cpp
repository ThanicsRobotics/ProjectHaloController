#include <powerbutton.h>

PowerButton::PowerButton(int gpioPin, std::shared_ptr<bool> shutdown)
    : button(gpioPin), shutdownIndicator(shutdown), holdTimer(3000)
{

}

void PowerButton::update()
{
    if (holdTimer.getHoldState(button.isPressed()) == HoldTimer::HoldState::DONE)
    {
        *shutdownIndicator = true;
    }
}
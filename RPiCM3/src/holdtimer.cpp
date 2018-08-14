#include <holdtimer.h>
#include <wiringPi.h>

HoldTimer::HoldTimer(int holdTime)
    : holdTime(holdTime)
{}

HoldTimer::HoldState HoldTimer::getHoldState(bool pressed)
{
    mPressed = pressed;
    checkHoldState();
    return state;
}

void HoldTimer::checkHoldState()
{
    switch(state)
    {
        case HoldState::INACTIVE:
            ifPressedStartHoldTimer();
        case HoldState::HOLDING:
            if(millis() - startTime > holdTime)
            {
                state = HoldState::DONE;
            }
            if(!mPressed)
            {
                state = HoldState::INACTIVE;
            }
            break;
        case HoldState::DONE:
            state = HoldState::INACTIVE;
            break;
        default:
            break;
    }
}

void HoldTimer::ifPressedStartHoldTimer()
{
    if(mPressed) state = HoldState::HOLDING;
    startTime = millis();
}
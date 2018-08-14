#ifndef HOLDTIMER_H
#define HOLDTIMER_H

class HoldTimer
{
public:
    enum class HoldState
    {
        INACTIVE = 0,
        HOLDING,
        DONE
    };
    HoldTimer(int holdTime);
    HoldState getHoldState(bool pressed);

private:
    bool mPressed = false;
    int startTime = 0;
    int holdTime = 0;
    HoldState state = HoldState::INACTIVE;

    void checkHoldState();
    void ifPressedStartHoldTimer();
};

#endif
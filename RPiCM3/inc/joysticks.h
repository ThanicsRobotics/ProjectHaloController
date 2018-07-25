#ifndef JOYSTICKS_H
#define JOYSTICKS_H

#include <adc.h>
#include <types.h>

class Joysticks
{
public:
    Joysticks();

    /// @brief Gives access to current joystick PWM positions.
    /// @param rcChannels Reference to a channels object, that
    /// will be modified to current joystick values.
    void getJoystickChannels(channels& rcChannels);

private:
    unsigned int lastTime = 0;

    /// @brief Converts 0-1023 point value to 0-3.3V.
    /// @return Value in volts, 0-3.3.
    float pointsToVolts(uint16_t points);

    /// @brief Converts 0-1023 points to 1000-2000us PWM value.
    /// @return Converted PWM value, 1000-2000.
    uint16_t pointsToPWM(uint16_t points);

    ADC adc;
};

#endif
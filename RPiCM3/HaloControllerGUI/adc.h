/// @file adc.h
/// @brief Definition for ADC class.
/// @author Andrew Loomis
/// @date 5/23/18

#ifndef ADC_H
#define ADC_H
#define RPI_COMPILE 1

#include <radio.h>
#include <array>

#if RPI_COMPILE

/// @brief Controls the 10 bit ADC on-board the controller.
class ADC
{
public:
    /// @brief Opens I2C port and sends setup byte.
    void setupADC();

    /// @brief Gives access to current joystick PWM positions.
    /// @param rcChannels Reference to a channels object, that
    /// will be modified to current joystick values.
    void getJoystickChannels(channels& rcChannels);

    /// @brief Closes I2C port.
    void closeADC();

private:
    int adcFd;  ///< File descriptor for ADC I2C port.

    /// @brief Converts the raw data from the ADC to a decimal 0-1023 number.
    /// @param data Array of data containing I2C block read from ADC.
    /// @param pointArray Reference to the array that will be modified to
    /// have new 0-1023 point values.
    void parseToPoints(uint8_t data[14], std::array<uint16_t, 7>& pointArray);

    /// @brief Converts 0-1023 point value to 0-3.3V.
    /// @return Value in volts, 0-3.3.
    float pointsToVolts(uint16_t points);

    /// @brief Converts 0-1023 points to 1000-2000us PWM value.
    /// @return Converted PWM value, 1000-2000.
    uint16_t pointsToPWM(uint16_t points);

    /// @brief Reads block ADC data.
    /// @param pointArray Reference to the array that will be modified to
    /// have new 0-1023 point values.
    void getADCData(std::array<uint16_t, 7>& pointArray);
};

#endif

#endif // ADC_H

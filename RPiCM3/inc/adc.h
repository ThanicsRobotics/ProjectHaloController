/// @file adc.h
/// @brief Definition for ADC class.
/// @author Andrew Loomis
/// @date 5/23/18

#ifndef ADC_H
#define ADC_H

#include <types.h>
#include <array>

/// @brief Controls the 10 bit ADC on-board the controller.
class ADC
{
public:
    ADC();
    ~ADC();

    /// @brief Opens I2C port and sends setup byte.
    void setupADC();
    
    /// @brief Reads block ADC data.
    /// @param pointArray Reference to the array that will be modified to
    /// have new 0-1023 point values.
    void getADCData(std::array<uint16_t, 7>& pointArray);

    uint16_t getChannelValue(int channelNumber);

    /// @brief Closes I2C port.
    void closeADC();

private:
    int adcFd;  ///< File descriptor for ADC I2C port.
    bool configured = false;

    std::array<uint16_t, 7> cachedReading;

    /// @brief Converts the raw data from the ADC to a decimal 0-1023 number.
    /// @param data Array of data containing I2C block read from ADC.
    /// @param pointArray Reference to the array that will be modified to
    /// have new 0-1023 point values.
    void parseToPoints(uint8_t data[14], std::array<uint16_t, 7>& pointArray);
};

#endif // ADC_H

#include <controller.h>
#include <wiringPi.h>

#include <iostream>
#include <types.h>
#include <util.h>
#include <memory>

Controller::Controller(std::shared_ptr<bool> shutdown)
    : shutdownIndicator(shutdown), radio(WLAN::DeviceType::HOST, "", 5000), 
    adc(std::make_shared<ADC>()), joysticks(adc), battery(adc), leftButton(38), 
    rightButton(41), powerButton(6, shutdown)
{
}

Controller::~Controller()
{
    std::cout << "Controller Shutting Down..." << std::endl;
}

void Controller::loopTest()
{
    while (!(*shutdownIndicator)) {
        // Diagnostics
        printStatus();
        powerButton.update();

        messagePacket msg;
        msg.rcChannels.pitchPWM = joystickPositions.pitchPWM;
        msg.rcChannels.rollPWM = joystickPositions.rollPWM;
        msg.rcChannels.yawPWM = joystickPositions.yawPWM;
        msg.rcChannels.throttlePWM = joystickPositions.throttlePWM;
        radio.checkBuffer();
        radio.send(msg);
        delay(100);
    }
}

void Controller::printStatus()
{
    updateJoysticks();
    std::cout << "=== Joystick Channels ===\n"
    << "Pitch : " << joystickPositions.pitchPWM
    << "\nRoll : " << joystickPositions.rollPWM
    << "\nYaw : " << joystickPositions.yawPWM
    << "\nThrottle : " << joystickPositions.throttlePWM
    << "\n=== Battery ==="
    << "\nVoltage : " << battery.getVoltage(10)
    << "\nCapacity : " << battery.getRemainingCapacity(10)
    << "\nCharging : " << (battery.isCharging() ? "Yes" : "No")
    << "\nCharge Current : " << battery.getChargingCurrent(10) << "mA"
    << "\n=== Buttons ==="
    << "\nLeft : " << leftButton.isPressed()
    << "\nRight : " << rightButton.isPressed()
    << "\nPower : " << powerButton.isPressed() << std::endl;
}
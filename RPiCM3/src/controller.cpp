#include <controller.h>
#include <wiringPi.h>

#include <iostream>
#include <types.h>
#include <util.h>

Controller::Controller(std::shared_ptr<bool> shutdown)
    : shutdownIndicator(shutdown), radio(WLAN::DeviceType::HOST, "", 5000), 
    joysticks(adc), battery(adc), leftButton(38), 
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
        channels joystickPositons;
        joysticks.getJoystickChannels(joystickPositons);
        std::cout << "=== Joystick Channels ===\n"
        << "Pitch : " << joystickPositons.pitchPWM
        << "\nRoll : " << joystickPositons.rollPWM
        << "\nYaw : " << joystickPositons.yawPWM
        << "\nThrottle : " << joystickPositons.throttlePWM
        << "\n=== Battery ==="
        << "\nVoltage : " << battery.getVoltage(10)
        << "\nCapacity : " << battery.getRemainingCapacity(10)
        << "\nCharging : " << (battery.isCharging() ? "Yes" : "No")
        << "\nCharge Current : " << battery.getChargingCurrent(10) << "mA"
        << "\n=== Buttons ==="
        << "\nLeft : " << leftButton.isPressed()
        << "\nRight : " << rightButton.isPressed()
        << "\nPower : " << powerButton.isPressed() << std::endl;
        powerButton.update();

        messagePacket msg;
        msg.rcChannels.pitchPWM = joystickPositons.pitchPWM;
        msg.rcChannels.rollPWM = joystickPositons.rollPWM;
        msg.rcChannels.yawPWM = joystickPositons.yawPWM;
        msg.rcChannels.throttlePWM = joystickPositons.throttlePWM;
        radio.checkBuffer();
        radio.send(msg);
        delay(100);
    }
}
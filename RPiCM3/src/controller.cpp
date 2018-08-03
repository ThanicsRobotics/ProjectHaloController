#include <controller.h>
#include <wiringPi.h>

#include <iostream>
#include <types.h>
#include <util.h>

Controller::Controller()
    : radio(WLAN::DeviceType::HOST, "", 5000), joysticks(adc),
    battery(adc)
{
    
}

void Controller::loopTest()
{
    while (1) {
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
        << "\nLeft : " << joysticks.isLeftButtonPressed()
        << "\nRight : " << joysticks.isRightButtonPressed() << std::endl;
        
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
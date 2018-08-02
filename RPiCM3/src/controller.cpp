#include <controller.h>
#include <wiringPi.h>

#include <iostream>
#include <types.h>

Controller::Controller()
    : radio(WLAN::DeviceType::HOST, "", 5000)
{
    
}

void Controller::loopTest()
{
    while (1) {
        // Diagnostics
        channels joystickPositons;
        adcController.getJoystickPositions(joystickPositons);
        std::cout << "=== Joystick Channels ===\n"
        << "Pitch : " << joystickPositons.pitchPWM
        << "\nRoll : " << joystickPositons.rollPWM
        << "\nYaw : " << joystickPositons.yawPWM
        << "\nThrottle : " << joystickPositons.throttlePWM
        << "\n=== Battery ==="
        << "\nVoltage : " << adcController.getBatteryVoltage()
        << "\nCapacity : " << adcController.getBatteryLife() 
        << "\nCharge Current : " << adcController.getChargeCurrent() * 1000 << "mA"
        << "\n=== Buttons ==="
        << "\nLeft : " << adcController.isLeftButtonPressed()
        << "\nRight : " << adcController.isRightButtonPressed() << std::endl;
        
        messagePacket msg;
        radio.checkBuffer();
        radio.send(msg);
        delay(100);
    }
}
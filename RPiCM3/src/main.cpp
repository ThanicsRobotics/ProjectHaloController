#include <stream.h>
#include <wiringPi.h>

// void shutdown(int signum) {
//     adc.closeADC();
//     radio.closeSerial();
// }

// void backendLoop() {
//     signal(SIGINT, shutdown);

//     adc.setupADC();
//     radio.setupSerial("/dev/serial0", 115200);
//     int timer, rcTimer = millis();

//     //Main loop
//     std::array<uint8_t, 15> dummyMsg = {0xFF, 0xFE, 0x01, 0x01, 0x00, 0x05, 0xDD, 0x05, 0xDD, 0x05, 0xDD, 0x05, 0xDD, 0xFD, 0xFC};
//     uint8_t count = 0;
//     while (1) {
//         channels rcChannels;
//         adc.getJoystickChannels(rcChannels);
//         if (count == 255) count = 0;
//         dummyMsg[4] = count;
//         dummyMsg[5] = (rcChannels.throttlePWM >> 8) & 0xFF;
//         dummyMsg[6] = rcChannels.throttlePWM & 0xFF;
//         dummyMsg[7] = (rcChannels.pitchPWM >> 8) & 0xFF;
//         dummyMsg[8] = rcChannels.pitchPWM & 0xFF;
//         dummyMsg[9] = (rcChannels.rollPWM >> 8) & 0xFF;
//         dummyMsg[10] = rcChannels.rollPWM & 0xFF;
//         dummyMsg[11] = (rcChannels.yawPWM >> 8) & 0xFF;
//         dummyMsg[12] = rcChannels.yawPWM & 0xFF;

//         radio.write(dummyMsg.data(), 15);
//         count++;
//     }
    

// }
Stream stream;

void callback(std::size_t size) {
    std::array<char, 128> buf = stream.getCurrentMessage();
    std::cout << "Received: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << buf[i];
    }
    std::cout << std::endl;
    stream.read(callback);
}

int main(int argc, char *argv[])
{
    
    stream.startHost();
    std::string msg = "hello1234";
    stream.write(msg);
    stream.read(callback);
    int i = 0;
    while (1)
    {
        std::cout << i++ << std::endl;
        delay(100);
        stream.checkBuffer();
    }


    return 0;
}

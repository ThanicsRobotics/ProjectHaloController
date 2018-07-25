#include <wlanradio.h>
#include <wiringPi.h>

int main(int argc, char *argv[])
{
    wiringPiSetupGpio();
    WLANRadio radio(WLAN::DeviceType::HOST, "", 5000);

    while (1) {
        messagePacket msg;
        radio.send(msg);
        delay(100);
    }

    return 0;
}

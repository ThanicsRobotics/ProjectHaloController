#include <controller.h>
#include <wiringPi.h>
#include <pigpio.h>

/// @brief Terminal signal handler (for ending program via terminal).
void signal_callback_handler(int signum) {
    gpioTerminate();
    exit(0);
}

int main(int argc, char *argv[])
{
    wiringPiSetupGpio();
    gpioInitialise();

    // Override pigpio SIGINT handling
    signal(SIGINT, signal_callback_handler);

    Controller controller;
    controller.loopTest();

    gpioTerminate();
    return 0;
}

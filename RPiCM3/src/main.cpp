#include <controller.h>
#include <wiringPi.h>
#include <pigpio.h>
#include <memory>

std::shared_ptr<bool> shutdownIndicator;

void shutdown()
{
    delay(500);
    gpioTerminate();
    system("halt");
}

/// @brief Terminal signal handler (for ending program via terminal).
void signal_callback_handler(int signum) {
    gpioTerminate();
    exit(0);
}

///
/// halo-controller executable
///

// int main(int argc, char *argv[])
// {
//     wiringPiSetupGpio();
//     gpioInitialise();

//     // Override pigpio SIGINT handling
//     signal(SIGINT, signal_callback_handler);
//     {
//         shutdownIndicator = std::make_shared<bool>(false);
//         Controller controller(shutdownIndicator);
//         controller.loopTest();
//     }
//     shutdown();
    
//     return 0;
// }

///
/// controller-status executable
///

int main(int argc, char *argv[])
{
    wiringPiSetupGpio();
    gpioInitialise();

    // Override pigpio SIGINT handling
    signal(SIGINT, signal_callback_handler);
    {
        shutdownIndicator = std::make_shared<bool>(false);
        Controller controller(shutdownIndicator);
        controller.printStatus();
    }
    gpioTerminate();
    
    return 0;
}
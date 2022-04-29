#include <cstdio>
#include <chrono>
#include <thread>
#include "UNR_GPIO_BCM2711.h"

int main()
{

    int ledPin = 3;
    int switchPin = 14;
    printf("GPIO Setup \n");

    setup();

    setup_gpio(ledPin, OUTPUT, PUD_UP);
    setup_gpio(switchPin, INPUT, PUD_UP);

    for (int i = 0; i < 5; i++)
    {
        if (input_gpio(switchPin) == 1)
        {
            printf("Switch value is high\n");
            output_gpio(ledPin, HIGH);
        }
        else
        {
            printf("Switch value is low\n");
            output_gpio(ledPin, LOW);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    printf("Finished \n");

    cleanup();

    return 0;
}
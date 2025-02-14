#include <Arduino.h>
#include <stdbool.h>
#include "led_driver.h"

static uint8_t pin_num = 0xFFU;
static bool initialized = false;

void led_driver_init(uint8_t pin)
{
    pin_num = pin;
    initialized = true;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LED_DRIVER_LOW);
}

led_driver_status_t led_driver_set_state(uint8_t state)
{
    led_driver_status_t status = LED_DRIVER_UNINITIALIZED;

    if (initialized)
    {
        status = LED_DRIVER_ERROR;
        if ((state == LED_DRIVER_HIGH) || (state == LED_DRIVER_LOW))
        {
            digitalWrite(pin_num, state);

            if (state == digitalRead(pin_num))
            {
                status = LED_DRIVER_OK;
            }
        }
    }

    return status;
}

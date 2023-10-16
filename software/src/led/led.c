/**
 * @file led.c
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief LED driver source
 * @version 1.0
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "led.h"

void LedCreate(LED_T *led, volatile uint8_t *_gpio_reg, volatile uint8_t *_gpio_port, uint8_t _gpio_pin)
{
    // Structure initialize
    led->state = LED_OFF;
    led->reg = _gpio_reg;
    led->port = _gpio_port;
    led->pin = _gpio_pin;

    // Hardware initialize
    // -- Register -> OUTPUT
    *led->reg |= (1 << led->pin);
    // -- Pin -> LOW
    *led->port &= ~(1 << led->pin);
}

void LedDestroy(LED_T *led)
{
    if (led != NULL){
        // Memory free
        free(led);
        led = NULL;
    }
}

void LedOn(LED_T *led)
{
    led->state = LED_ON;
    *led->port |= (1 << led->pin);
}

void LedOff(LED_T *led)
{
    led->state = LED_OFF;
    *led->port &= ~(1 << led->pin);
}

void LedToogle(LED_T *led)
{
    if (led->state == LED_ON)
    {
        LedOff(led);
    }
    else
    {
        LedOn(led);
    }
}

void LedSetState(LED_T *led, LED_STATE_T state)
{
    if (state == LED_ON)
    {
        LedOn(led);
    }
    else
    {
        LedOff(led);
    }
}

LED_STATE_T LedGetState(LED_T *led)
{
    return led->state;
}

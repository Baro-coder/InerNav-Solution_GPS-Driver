/**
 * @file led.h
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief LED driver interface
 * @version 1.0
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _LED_H
#define _LED_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Abstract LED state
 * 
 * State of @e digital pin bind to @e led device
 */
typedef enum _led_state_t
{
    LED_OFF, /*!< LED OFF value */
    LED_ON   /*!< LED ON value */
} LED_STATE_T;

/**
 * @brief LED structure
 * 
 * Structure to handle the @e digital pin operations for @e led device
 */
typedef struct _led_t
{
    LED_STATE_T state;      /*!< LED State */
    volatile uint8_t *reg;  /*!< LED GPIO register */
    volatile uint8_t *port; /*!< LED GPIO port */
    uint8_t pin;            /*!< LED GPIO pin */
} LED_T;


/**
 * @brief LED creating and initializing function
 *
 * Caller has to allocate memory for @a led himself and pass the rest of parameters.
 * Then the function initialize hardware registers and @ref LED_T @a led structure to prepare for further use.
 * 
 * @param led a LED structure pointer
 * @param _gpio_reg LED GPIO register
 * @param _gpio_port LED GPIO port
 * @param _gpio_pin LED GPIO pin
 */
void LedCreate(LED_T *led, volatile uint8_t *_gpio_reg, volatile uint8_t *_gpio_port, uint8_t _gpio_pin);

/**
 * @brief LED structure destructor
 *
 * Funcion deinitialize hardware registers and free allocated memory for @a led
 * 
 * @warning Use only after previously allocated memory for!
 * 
 * @param led a LED structure pointer
 */
void LedDestroy(LED_T *led);

/**
 * @brief Change LED state to ON
 * 
 * @param led a LED structure pointer
 */
void LedOn(LED_T *led);

/**
 * @brief Change LED state to OFF
 *
 * @param led a LED structure pointer
 */
void LedOff(LED_T *led);

/**
 * @brief Change LED state (ON -> OFF) or (OFF -> ON)
 *
 * @param led a LED structure pointer
 */
void LedToogle(LED_T *led);

/**
 * @brief LED's state setter
 *
 * @param led a LED structure pointer
 * @param state expected LED state
 */
void LedSetState(LED_T *led, LED_STATE_T state);

/**
 * @brief LED's state getter
 *
 * @param led a LED structure pointer
 * @return @a led_state_t LED's state
 */
LED_STATE_T LedGetState(LED_T *led);

#endif
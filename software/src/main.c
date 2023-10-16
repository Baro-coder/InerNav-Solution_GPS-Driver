/**
 * @file main.c
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief MCU program main file
 * @version 1.0
 * @date 2023-10-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"

/**
 * @brief Program entry point
 *
 * @return @a int status code
 */
int main(void)
{
    LED_T *ledYellow = (LED_T *)malloc(sizeof(LED_T));
    LedCreate(ledYellow, &DDRB, &PORTB, PB0);

    while (1)
    {
        LedToogle(ledYellow);
        _delay_ms(100);
    }

    LedDestroy(ledYellow);

    return 0;
}

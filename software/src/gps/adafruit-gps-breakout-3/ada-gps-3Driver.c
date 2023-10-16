/**
 * @file ada-gps-3Driver.c
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief Adafruit GPS Breakout v3 module driver source
 * @version 1.0
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ada-gps-3.h"
#include "../gps.h"


float GPS_getLattitude(void){
    return 22.124;
}

float GPS_getLongitude(void){
    return 56.034;
}

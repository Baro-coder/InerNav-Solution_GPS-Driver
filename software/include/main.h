/**
 * @file main.h
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief MCU program main header
 * @version 1.0
 * @date 2023-10-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _MAIN_H
#define _MAIN_H

//! AVR Device Model
#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

//! CPU Frequency
#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

//! Compiler optimizations enabled
#ifndef __OPTIMIZE__
    #define __OPTIMIZE__
#endif


#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

#include "led/led.h"
#include "gps/gps.h"
#include "nmea/nmea.h"
#include "comm-link/driver.h"


#endif
/**
 * @file gps.h
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief Embedded GPS module driver interface
 * @version 1.0
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _GPS_H
#define _GPS_H


float GPS_getLattitude(void);
float GPS_getLongitude(void);

void GPS_Enable(void);
void GPS_Disable(void);

#endif
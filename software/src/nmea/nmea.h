/**
 * @file nmea.h
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief NMEA 0183 protocol messages parser interface
 * 
 * @e National @e Marine @e Electronics @e Association protocol handler module interface
 * 
 * @version 1.0
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _NMEA_H
#define _NMEA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "_nmea_codes.h"
#include "_nmea_structs.h"

//! NMEA module boolean definition of @c True
#define NMEA_TRUE 1
//! NMEA module boolean definition of @c False
#define NMEA_FALSE 0

//! NMEA response code : @e Invalid @e CRC
#define NMEA_ERR_CRC 1
//! NMEA response code : @e Unknown @e Satellite @e System
#define NMEA_ERR_UNKNOWN_SYSTEM 2
//! NMEA response code : @e Unknown @e Sentence @e Type
#define NMEA_ERR_UNKNOWN_SENTENCE 3
//! NMEA response code : @e Parser @e error
#define NMEA_ERR_PARSE 4
//! NMEA response code : @e OK
#define NMEA_OK 0

/**
 * @brief NMEA Message data structure
 * 
 */
typedef struct _nmea_message_t
{
    NMEA_SAT_SYS_T satelliteSystem;         /*!< Satellite System (see @ref NMEA_SAT_SYS_T) */
    NMEA_SENTENCE_TYPE_T sentenceType;      /*!< Sentence Type ((see @ref NMEA_SENTENCE_TYPE_T)) */
    void* data;                             /*!< Pointer to appropriate payload data structure */
} NMEA_MESSAGE_T;

/**
 * @brief NMEA CRC calculate function
 * 
 * Processing the binary XOR operation between all characters in the sentence 
 * (between @ref NMEA_START_CHAR and @ref NMEA_CONTROL_CHAR)
 * 
 * @param msg NMEA message buffer handler
 * @return On @e SUCCESS : @a uint16_t The checksum validation value.
 * On @e ERROR : @c 0x00 value
 */
uint16_t NMEA_calculateCRC(char *msg);

/**
 * @brief NMEA CRC retrieval function
 *
 * Retrieve hexadecimal value of two-char sequence from @ref NMEA_CONTROL_CHAR
 *
 * @param msg NMEA message buffer handler
 * @return On @e SUCCESS : @a uint16_t CRC decimal value.
 *  On @e ERROR: @c 0x00 value
 */
uint16_t NMEA_retrieveCRC(char *msg);

/**
 * @brief NMEA CRC checker
 *
 * Firstly the function retrieves the CRC value from @e msg buffer,
 * then it calculates appropriate CRC itself and
 * finally it compares these two values.
 *
 * @param msg NMEA message buffer handler
 * @return On @e SUCCESS : @ref NMEA_TRUE. On @e ERROR : @ref NMEA_FALSE
 */
uint8_t NMEA_checkCRC(char *msg);

/**
 * @brief NMEA message parser
 *
 *
 * @param msg NMEA message buffer handler
 * @param nmeaMsg NMEA message data structure handler
 * @return On @e SUCCESS : @ref NMEA_OK.
 * On @e ERROR with CRC : @ref NMEA_ERR_CRC
 * On @e ERROR with satellite system detecting : @ref NMEA_ERR_UNKNOWN_SYSTEM.
 * On @e ERROR with sentence type detecting : @ref NMEA_ERR_UNKNOWN_SENTENCE.
 * On @e ERROR with message parsing : @ref NMEA_ERR_PARSE.
 */
uint8_t NMEA_parseMessage(char *msg, NMEA_MESSAGE_T *nmeaMsg);

#endif
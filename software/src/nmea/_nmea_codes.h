/**
 * @file _nmea_codes.h
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief NMEA Messages Sentences factors' codes
 * @version 1.0
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _NMEA_CODES_H
#define _NMEA_CODES_H

//! NMEA Compass Direction @e North
#define NMEA_DIRECTION_NORTH 'N'
//! NMEA Compass Direction @e East
#define NMEA_DIRECTION_EAST  'E'
//! NMEA Compass Direction @e South
#define NMEA_DIRECTION_SOUTH 'S'
//! NMEA Compass Direction @e West
#define NMEA_DIRECTION_WEST 'W'

//! NMEA Position Status @e Valid
#define NMEA_POS_STATUS_VALID 'A'
//! NMEA Position Status @e Invalid
#define NMEA_POS_STATUS_INVALID 'V'

//! NMEA Message character : @e start
#define NMEA_START_CHAR '$'
//! NMEA Message character : @e delimiter
#define NMEA_DELIMITER_CHAR ','
//! NMEA Message character : @e control
#define NMEA_CONTROL_CHAR '*'


//! Sattelite System : @a GPS
#define NMEA_SAT_SYS_GPS "GP"
//! Sattelite System : @a Glonass
#define NMEA_SAT_SYS_GLO "GL"
//! Sattelite System : @a BeiDou
#define NMEA_SAT_SYS_BDS "BD"
//! Sattelite System : @a GNSS
#define NMEA_SAT_SYS_GNS "GN"

typedef enum _nmea_satsys_t
{
    UNKNOWN_SYSTEM,
    GPS,
    Glonass,
    BeiDou,
    GNSS,
    NUM_SYSTEMS
} NMEA_SAT_SYS_T;


//! NMEA Sentence type : @e Global @e Positioning @e System @a Fix @e Data
#define NMEA_MSG_GGA "GGA"
//! NMEA Sentence type : @e Satellites @e in @e view
#define NMEA_MSG_GSV "GSV"
//! NMEA Sentence type : @e Reccommended @e minimum @e specific @e GPS/Transit @e data
#define NMEA_MSG_RMC "RMC"

typedef enum _nmea_sentence_type_t
{
    UNKNOWN_SENTENCE,
    GGA,
    GSV,
    RMC,
    NUM_SENTENCE_TYPES
} NMEA_SENTENCE_TYPE_T;

#endif
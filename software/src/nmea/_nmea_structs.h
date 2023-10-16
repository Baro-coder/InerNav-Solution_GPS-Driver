/**
 * @file _nmea_structs.h
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief NMEA Messages abstract data structures representations
 * @version 1.0
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _NMEA_STRUCTS_H
#define _NMEA_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "_nmea_codes.h"

/**
 * @brief Compass directions enumeration
 */
typedef enum _nmea_compass_direction_t
{
    North = NMEA_DIRECTION_NORTH, /*!< direction : North (expanded to @ref NMEA_DIRECTION_NORTH)*/
    East = NMEA_DIRECTION_EAST,   /*!< direction : East  (expanded to @ref NMEA_DIRECTION_EAST)*/
    South = NMEA_DIRECTION_SOUTH, /*!< direction : South (expanded to @ref NMEA_DIRECTION_SOUTH)*/
    West = NMEA_DIRECTION_WEST    /*!< direction : West  (expanded to @ref NMEA_DIRECTION_WEST)*/
} NMEA_COMPASS_DIRECTION_T;

/**
 * @brief Position status enumeration
 */
typedef enum _nmea_position_status_t
{
    VALID = NMEA_POS_STATUS_VALID,      /*!< valid position status   (expanded to @ref NMEA_POS_STATUS_VALID)*/
    INVALID = NMEA_POS_STATUS_INVALID   /*!< invalid position status (expanded to @ref NMEA_POS_STATUS_INVALID)*/
} NMEA_POSITION_STATUS_T;

/**
 * @brief Time structure
 */
typedef struct _nmea_time
{
    uint8_t hrs;    /*!< Hours */
    uint8_t min;    /*!< Minutes */
    uint8_t sec;    /*!< Seconds */
    uint16_t msec;  /*!< Miliseconds */
} NMEA_TIME_T;

/**
 * @brief Date structure
 */
typedef struct _nmea_date
{
    uint8_t day;    /*!< Day of month */
    uint8_t mon;    /*!< Month */
    uint16_t year;  /*!< Year */
} NMEA_DATE_T;

/**
 * @brief Datetime structure
 */
typedef struct _nmea_datetime
{
    NMEA_DATE_T date;   /*!< date structure */
    NMEA_TIME_T time;   /*!< time structure */
} NMEA_DATETIME_T;

/**
 * @brief NMEA GSV satellite info
 *
 * Data structure for satellite info from NMEA GSV Message
 */
typedef struct _nmea_msg_gsv_satellite_t
{
    uint8_t number;            /*!< The satellite number */
    uint16_t elevation;        /*!< The satellite elevation */
    uint8_t azimuth;           /*!< The satellite azimuth */
    uint32_t signalNoiseRatio; /*!< Signal to noise ratio  */
} NMEA_MSG_GSV_SATELLITE_T;

/**
 * @brief NMEA GGA sentence data structure
 *
 * Data structure for sentence type :
 * @e Global @e Positioning @e System @e Fix @e Data
 */
typedef struct _nmea_msg_gga_t
{
    NMEA_TIME_T time;                            /*!< Current time */
    float latitude;                              /*!< Latitude */
    NMEA_COMPASS_DIRECTION_T latitudeDirection;  /*!< Latitude compass direction */
    float longitude;                             /*!< Longitude */
    NMEA_COMPASS_DIRECTION_T longitudeDirection; /*!< Longitutde compass direction */
    uint8_t fixType;                             /*!< Fix type (0 - no fix, 1 - GPS, 2 - DGPS) */
    uint8_t satellitesCount;                     /*!< Number of satellites used for fix */
    float hdp;                                   /*!< Horizontal dilution of precision */
    float altitude;                              /*!< Altitude above sea level */
    char altitudeUnit;                           /*!< Altitude units */
    float meanSeaLevel;                          /*!< Height of mean sea level above WGS-84 earth ellipsoid */
    char geoidSeperationUnit;                    /*!< Units of the above geoid seperation */
    uint32_t lastCorrectionTimeSince;            /*!< Time since last differential correction (ignored if inactive) */
    uint8_t stationID;                           /*!< Differential station ID (ignored if inactive) */
    uint16_t checksum;                           /*!< Checksum validation value */
} NMEA_MSG_GGA_T;



/**
 * @brief NMEA GSV sentence data structure
 *
 * Data structure for sentence type :
 * @e Satellites @e in @e view
 * @note @ref satellitesCount contains amount of satellites included in the whole sequence of sentences.
 * @ref _sentenceSatellitesCount is a @ref satellites array size.
 */
typedef struct _nmea_msg_gsv_t
{
    uint8_t sentencesCount;               /*!< The number of sentences in sequence */
    uint8_t sentenceNumber;               /*!< The number of this sentence */
    uint8_t satellitesCount;              /*!< The number of satellites */
    NMEA_MSG_GSV_SATELLITE_T *satellites; /*!< Satellites info */
    uint16_t checksum;                    /*!< Checksum validation value */
    uint8_t _sentenceSatellitesCount;     /*!< The number of satellites included in this sentence only*/
} NMEA_MSG_GSV_T;

/**
 * @brief NMEA RMC sentence data structure
 *
 * Data structure for sentence type :
 * @e Reccommended @e minimum @e specific @e GPS/Transit @e data
 */
typedef struct _nmea_msg_rmc_t
{
    NMEA_DATETIME_T datetime;                               /*!< Current date and time*/
    NMEA_POSITION_STATUS_T positionStatus;                  /*!< Position status */
    float latitude;                                         /*!< Latitude */
    float longitude;                                        /*!< Longitude */
    NMEA_COMPASS_DIRECTION_T latitudeDirection;             /*!< Latitude compass direction */
    NMEA_COMPASS_DIRECTION_T longitudeDirection;            /*!< Longitutde compass direction */
    float speed;                                            /*!< Speed in knots per hour */
    float heading;                                          /*!< Heading / azimuth */
    float magneticVariation;                                /*!< Magnetic variation */
    NMEA_COMPASS_DIRECTION_T magneticVariationDirection;    /*!< Magnetic variation direction */
    uint8_t checksum;                                       /*!< Checksum validation value */
} NMEA_MSG_RMC_T;

#endif
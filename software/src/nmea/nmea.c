/**
 * @file nmea.c
 * @author Bartłomiej Szykuła (bartlomiej.szykula@student.wat.edu.pl)
 * @brief NMEA 0183 protocol messages parser source
 * @version 1.0
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "nmea.h"

static char *__NMEA_SAT_SYSTEMS_SEQUENCES[] = {
    NMEA_SAT_SYS_GPS,
    NMEA_SAT_SYS_GLO,
    NMEA_SAT_SYS_BDS,
    NMEA_SAT_SYS_GNS
};

static char *__NMEA_SAT_SENTENCES_TYPES_SEQUENCES[] = {
    NMEA_MSG_GGA,
    NMEA_MSG_GSV,
    NMEA_MSG_RMC
};


static NMEA_TIME_T __NMEA_parseUtcTime(char* buffer) {
    NMEA_TIME_T time;
    time.hrs = 0;
    time.min = 0;
    time.sec = 0;
    time.msec = 0;
    return time;
}

/**
 * @brief NMEA satellite system detector
 * 
 * @param msg NMEA message buffer handler
 * @return NMEA_SAT_SYS_T 
 */
static NMEA_SAT_SYS_T __NMEA_detectSatelliteSystem(char *msg)
{
    NMEA_SAT_SYS_T system = UNKNOWN_SYSTEM;
    size_t length = strlen(msg);
    char *systemSequence = (char *)malloc(3 * sizeof(char));
    memset(systemSequence, 0, 3);

    if (msg != NULL && msg[0] != '\0')
    {
        for (size_t i = 0; i < length; i++)
        {
            if (msg[i] == NMEA_START_CHAR)
            {
                if (length >= i + 2)
                {
                    systemSequence[0] = msg[++i];
                    systemSequence[1] = msg[++i];
                }
                break;
            }
        }

        if (systemSequence[0] != 0 && systemSequence[1] != 0)
        {
            uint8_t index = 0;
            for (; index < NUM_SYSTEMS - 1; index++)
            {
                if (strncmp(systemSequence, __NMEA_SAT_SYSTEMS_SEQUENCES[index], 2) == 0)
                {
                    break;
                }
            }

            if (index >= 0 && index < NUM_SYSTEMS - 1)
            {
                system = (NMEA_SAT_SYS_T)++index;
            }
        }
    }

    free(systemSequence);
    return system;
}

static NMEA_SENTENCE_TYPE_T __NMEA_detectSentenceType(char *msg)
{
    NMEA_SENTENCE_TYPE_T sentence = UNKNOWN_SENTENCE;
    size_t length = strlen(msg);
    char *sentenceSequence = (char *)malloc(8 * sizeof(char));
    memset(sentenceSequence, 0, 8);

    if (msg != NULL && msg[0] != '\0')
    {
        for (size_t i = 0; i < length; i++)
        {
            if (msg[i] == NMEA_START_CHAR)
            {
                if (length > i + 2)
                {
                    i += 2;
                    for (uint8_t j = i; j < i + 8; j++)
                    {
                        if (msg[j] == NMEA_DELIMITER_CHAR)
                        {
                            break;
                        }
                        sentenceSequence[j - i] = msg[j + 1];
                    }
                }
                break;
            }
        }

        uint8_t index = 0;
        for (; index < NUM_SENTENCE_TYPES - 1; index++)
        {
            if (strncmp(sentenceSequence, __NMEA_SAT_SENTENCES_TYPES_SEQUENCES[index], strlen(__NMEA_SAT_SENTENCES_TYPES_SEQUENCES[index])) == 0)
            {
                break;
            }
        }

        if (index >= 0 && index < NUM_SENTENCE_TYPES - 1)
        {
            sentence = (NMEA_SENTENCE_TYPE_T)++index;
        }
    }

    free(sentenceSequence);
    return sentence;
}

static void __NMEA_parse_GGA(char* msg, NMEA_MESSAGE_T* nmeaMsg, uint16_t crc) 
{
    size_t length = strlen(msg);
    NMEA_MSG_GGA_T *data = (NMEA_MSG_GGA_T *)malloc(sizeof(NMEA_MSG_GGA_T));
    
    data->checksum = crc;

    uint8_t started = NMEA_FALSE;
    while(msg++){
        if(*msg == NMEA_DELIMITER_CHAR && started == NMEA_TRUE) {
            break;
        }
        if(*msg == NMEA_START_CHAR) {
            started = NMEA_TRUE;
        }
    }
    if(started != NMEA_TRUE) {
        free(data);
        data = NULL;
        return;
    }

    char* token;
    token = strtok((char*)msg, NMEA_DELIMITER_CHAR);

    char time[9];
    strcpy(time, token);
    data->time = __NMEA_parseUtcTime(time);
    token = strtok(NULL, ",");

    data->latitude = strtod(token, NULL);
    token = strtok(NULL, ",");
    data->latitudeDirection = token[0];
    token = strtok(NULL, ",");
    data->longitude = strtod(token, NULL);
    token = strtok(NULL, ",");
    data->longitudeDirection = token[0];
    token = strtok(NULL, ",");
    data->fixType = atoi(token);
    token = strtok(NULL, ",");
    data->satellitesCount = atoi(token);
    token = strtok(NULL, ",");
    data->hdp = strtod(token, NULL);
    token = strtok(NULL, ",");
    data->altitude = strtod(token, NULL);
    token = strtok(NULL, ",");
    data->altitudeUnit = token[0];
    token = strtok(NULL, ",");
    data->meanSeaLevel = strtod(token, NULL);
    token = strtok(NULL, ",");
    data->geoidSeperationUnit = token[0];
    token = strtok(NULL, ",");
    data->lastCorrectionTimeSince = atoi(token);
    token = strtok(NULL, ",");
    data->stationID = atoi(token);
    token = strtok(NULL, ",");

    nmeaMsg->data = data;
}

static void __NMEA_parse_GSV(char *msg, NMEA_MESSAGE_T *nmeaMsg, uint16_t crc)
{
    size_t length = strlen(msg);
    NMEA_MSG_GSV_T *data = (NMEA_MSG_GSV_T *)malloc(sizeof(NMEA_MSG_GSV_T));

    data->checksum = crc;

    for (size_t i = 0; i < length; i++)
    {

    }

    nmeaMsg->data = data;
}

static void __NMEA_parse_RMC(char *msg, NMEA_MESSAGE_T *nmeaMsg, uint16_t crc)
{
    size_t length = strlen(msg);
    NMEA_MSG_RMC_T *data = (NMEA_MSG_RMC_T *)malloc(sizeof(NMEA_MSG_RMC_T));

    data->checksum = crc;

    for (size_t i = 0; i < length; i++)
    {

    }

    nmeaMsg->data = data;
}

static uint16_t __NMEA_HexToUInt(char c)
{
    // ASCII [A-F]
    if (c >= 'A' && c <= 'F') {
        return (uint16_t)(c - 'A' + 10);
    }

    // ASCII [a-f]
    if (c >= 'a' && c <= 'f') {
        return (uint16_t)(c - 'a' + 10);
    }

    // ASCII [0-9]
    if (c >= '0' && c <= '9')
    {
        return (uint16_t)(c - '0');
    }

    return (uint16_t)c;
}


uint16_t NMEA_retrieveCRC(char *msg) {
    // Prepare data containers
    uint16_t crc = 0;
    size_t length = strlen(msg);
    char *crcSequence = (char *)malloc(2 * sizeof(char));
    memset(crcSequence, 0, 2);

    // Check if `msg` pointer is valid
    if(msg != NULL && msg[0] != '\0') {
        // Iterate over `msg`
        for(size_t i = 0; i < length; i++) {
            // Get to the `NMEA_CONTROL_CHAR`
            if(msg[i] == NMEA_CONTROL_CHAR) {
                // Read the following two characters and quit the loop
                crcSequence[0] = msg[++i];
                crcSequence[1] = msg[++i];
                break;
            }
        }
    }
    // Check if the read characters are valid
    if(crcSequence[0] != 0 && crcSequence[1] != 0){
        // Convert two-char sequence into decimal value
        for(int i = 0; i < 2; i++) {
            uint16_t decVal = __NMEA_HexToUInt(crcSequence[i]);
            // Check the convertion status
            if (decVal != crcSequence[i]) {
                crc += (decVal * pow(16, (1 - i)));
            } else {
                crc = 0;
                break;
            }
        }
    }
    // Clean up and return
    free(crcSequence);
    return crc;
}

uint16_t NMEA_calculateCRC(char *msg) {
    // Prepare data containers
    size_t length = strlen(msg);
    uint16_t crc = 0;

    // Check if `msg` pointer is valid
    if(msg != NULL && msg[0] != '\0')
    {
        // Iterate over `msg`
        for (size_t i = 0; i < length; i++)
        {
            // Get to the `NMEA_START_CHAR` and start the calculate procedure
            if (msg[i] == NMEA_START_CHAR)
            {
                crc = 0;
            }
            // If end of sentence, then quit the loop
            else if (msg[i] == NMEA_CONTROL_CHAR || msg[i] == '\0')
            {
                break;
            }
            // Calculate each sentence's character (XOR) 
            else
            {
                crc ^= msg[i];
            }
        }
    }

    return crc;
}

uint8_t NMEA_checkCRC(char *msg) {
    uint16_t crc_r = NMEA_retrieveCRC(msg);
    uint16_t crc_c = NMEA_calculateCRC(msg);

    if(crc_r == 0 || crc_c == 0 || crc_r != crc_c) {
        return NMEA_FALSE;
    } else {
        return NMEA_TRUE;
    }
}

uint8_t NMEA_parseMessage(char *msg, NMEA_MESSAGE_T *nmeaMsg)
{
    // CRC check
    if(NMEA_checkCRC(msg) == NMEA_FALSE) {
        return NMEA_ERR_CRC;
    }
    uint16_t crc = NMEA_retrieveCRC(msg);

    // Detecting satellite system
    NMEA_SAT_SYS_T satSys = __NMEA_detectSatelliteSystem(msg);
    if (satSys == UNKNOWN_SYSTEM) {
        return NMEA_ERR_UNKNOWN_SYSTEM;
    }

    // Detecting sentence type
    NMEA_SENTENCE_TYPE_T sentenceType = __NMEA_detectSentenceType(msg);
    if (sentenceType == UNKNOWN_SENTENCE) {
        return NMEA_ERR_UNKNOWN_SENTENCE;
    }

    // Sentence type interpreter and parser link
    switch (sentenceType) {
        case GGA:
            __NMEA_parse_GGA(msg, nmeaMsg, crc);
            break;
        case GSV:
            __NMEA_parse_GSV(msg, nmeaMsg, crc);
            break;
        case RMC:
            __NMEA_parse_RMC(msg, nmeaMsg, crc);
            break;
    }

    // Parse check
    if(nmeaMsg->data == NULL) {
        nmeaMsg = NULL;
        return NMEA_ERR_PARSE;
    } else {
        nmeaMsg->satelliteSystem = satSys;
        nmeaMsg->sentenceType = sentenceType;
    }

    return NMEA_OK;
}
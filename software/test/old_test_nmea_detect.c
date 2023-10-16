#include <unity.h>
#include <string.h>
#include "nmea/nmea.h"

void test_detectSatelliteSystem_Valid()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";
    char *msg_2 = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    char *msg_3 = "$GP";
    char *msg_4 = "$GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7F";
    char *msg_5 = "$GLGSV,3,1,11,65,47,150,40,66,42,130,40,67,37,044,34,68,29,343,33*64\r\n";
    char *msg_6 = "$BDGSV,3,1,11,134,48,153,40,135,43,134,36,137,47,211,40,138,46,037,38*67\r\n";
    char *msg_7 = "$GNGLL,4916.45,N,12311.12,W,225444,A,*1D";

    // Action & Assertion
    TEST_ASSERT_EQUAL(GPS, NMEA_detectSatelliteSystem(msg_1));
    TEST_ASSERT_EQUAL(GPS, NMEA_detectSatelliteSystem(msg_2));
    TEST_ASSERT_EQUAL(GPS, NMEA_detectSatelliteSystem(msg_3));
    TEST_ASSERT_EQUAL(GPS, NMEA_detectSatelliteSystem(msg_4));
    TEST_ASSERT_EQUAL(Glonass, NMEA_detectSatelliteSystem(msg_5));
    TEST_ASSERT_EQUAL(BeiDou, NMEA_detectSatelliteSystem(msg_6));
    TEST_ASSERT_EQUAL(GNSS, NMEA_detectSatelliteSystem(msg_7));
}

void test_detectSatelliteSystem_Invalid_NotRecognized()
{
    // Preparation
    char *msg_1 = "$GKGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";
    char *msg_2 = "$LGGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    char *msg_3 = "$POPRMC,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*44";
    char *msg_4 = "$KOGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7F";
    char *msg_5 = "$WAGSV,3,1,11,65,47,150,40,66,42,130,40,67,37,044,34,68,29,343,33*64\r\n";
    char *msg_6 = "$DBGSV,3,1,11,134,48,153,40,135,43,134,36,137,47,211,40,138,46,037,38*67\r\n";
    char *msg_7 = "$QGLL,4916.45,N,12311.12,W,225444,A,*1D";

    // Action & Assertion
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_1));
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_2));
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_3));
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_4));
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_5));
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_6));
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_7));
}

void test_detectSatelliteSystem_Invalid_NoStartChar()
{
    // Preparation
    char *msg_1 = "GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";

    // Action & Assertion
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_1));
}

void test_detectSatelliteSystem_Invalid_MessageTooShort()
{
    // Preparation
    char *msg_1 = "$";
    char *msg_2 = "$G";

    // Action & Assertion
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_1));
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(msg_2));
}

void test_detectSatelliteSystem_Invalid_NullMessagePointer()
{
    // Preparation
    char *message = (char *)malloc(32 * sizeof(char));

    // Action & Assertion
    TEST_ASSERT_EQUAL(UNKNOWN_SYSTEM, NMEA_detectSatelliteSystem(message));

    // Clean up
    free(message);
}



void test_detectSentenceType_Valid()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";
    char *msg_2 = "$GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7F";
    char *msg_3 = "$GPRMC,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*44";

    // Action & Assertion
    TEST_ASSERT_EQUAL(GGA, NMEA_detectSentenceType(msg_1));
    TEST_ASSERT_EQUAL(GSV, NMEA_detectSentenceType(msg_2));
    TEST_ASSERT_EQUAL(RMC, NMEA_detectSentenceType(msg_3));
}

void test_detectSentenceTypeSentenceTypevalid_NotRecognized()
{
    // Preparation
    char *msg_1 = "$GPAGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";
    char *msg_2 = "$GPASA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    char *msg_3 = "$GPAMG,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*44";
    char *msg_4 = "$GPGSF,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7F";
    char *msg_5 = "$GLASV,3,1,11,65,47,150,40,66,42,130,40,67,37,044,34,68,29,343,33*64\r\n";
    char *msg_6 = "$BDASA,3,1,11,134,48,153,40,135,43,134,36,137,47,211,40,138,46,037,38*67\r\n";
    char *msg_7 = "$GPAH,4916.45,N,12311.12,W,225444,A,*1D";

    // Action & Assertion
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_1));
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_2));
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_3));
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_4));
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_5));
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_6));
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_7));
}

void test_detectSentenceType_Invalid_NoStartChar()
{
    // Preparation
    char *msg_1 = "GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";

    // Action & Assertion
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_1));
}

void test_detectSentenceType_Invalid_MessageTooShort()
{
    // Preparation
    char *msg_1 = "$";
    char *msg_2 = "$G";
    char *msg_3 = "$GP";

    // Action & Assertion
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_1));
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_2));
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(msg_3));
}

void test_detectSentenceType_Invalid_NullMessagePointer()
{
    // Preparation
    char *message = (char *)malloc(32 * sizeof(char));

    // Action & Assertion
    TEST_ASSERT_EQUAL(UNKNOWN_SENTENCE, NMEA_detectSentenceType(message));

    // Clean up
    free(message);
}

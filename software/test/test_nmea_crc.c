#include <unity.h>
#include <string.h>
#include "nmea/nmea.h"


void test_calculateCRC_Valid()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";
    char *msg_2 = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    char *msg_3 = "$GPRMC,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*44";
    char *msg_4 = "$GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7F";
    char *msg_5 = "$GLGSV,3,1,11,65,47,150,40,66,42,130,40,67,37,044,34,68,29,343,33*64\r\n";
    char *msg_6 = "$BDGSV,3,1,11,134,48,153,40,135,43,134,36,137,47,211,40,138,46,037,38*67\r\n";
    char *msg_7 = "$GPGLL,4916.45,N,12311.12,W,225444,A,*1D";

    // Action & Assertion
    TEST_ASSERT_EQUAL(0x69, NMEA_calculateCRC(msg_1));
    TEST_ASSERT_EQUAL(0x39, NMEA_calculateCRC(msg_2));
    TEST_ASSERT_EQUAL(0x44, NMEA_calculateCRC(msg_3));
    TEST_ASSERT_EQUAL(0x7F, NMEA_calculateCRC(msg_4));
    TEST_ASSERT_EQUAL(0x64, NMEA_calculateCRC(msg_5));
    TEST_ASSERT_EQUAL(0x67, NMEA_calculateCRC(msg_6));
    TEST_ASSERT_EQUAL(0x1D, NMEA_calculateCRC(msg_7));
}

void test_calculateCRC_Valid_NoStartChar()
{
    // Preparation
    char *msg_1 = "GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";
    char *msg_2 = "GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    char *msg_3 = "GPRMC,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*44";
    char *msg_4 = "GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7F";
    char *msg_5 = "GLGSV,3,1,11,65,47,150,40,66,42,130,40,67,37,044,34,68,29,343,33*64\r\n";
    char *msg_6 = "BDGSV,3,1,11,134,48,153,40,135,43,134,36,137,47,211,40,138,46,037,38*67\r\n";
    char *msg_7 = "GPGLL,4916.45,N,12311.12,W,225444,A,*1D";

    // Action & Assertion
    TEST_ASSERT_EQUAL(0x69, NMEA_calculateCRC(msg_1));
    TEST_ASSERT_EQUAL(0x39, NMEA_calculateCRC(msg_2));
    TEST_ASSERT_EQUAL(0x44, NMEA_calculateCRC(msg_3));
    TEST_ASSERT_EQUAL(0x7F, NMEA_calculateCRC(msg_4));
    TEST_ASSERT_EQUAL(0x64, NMEA_calculateCRC(msg_5));
    TEST_ASSERT_EQUAL(0x67, NMEA_calculateCRC(msg_6));
    TEST_ASSERT_EQUAL(0x1D, NMEA_calculateCRC(msg_7));
}

void test_calculateCRC_Valid_NoControlChar()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,";
    char *msg_2 = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1";
    char *msg_3 = "$GPRMC,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W";
    char *msg_4 = "$GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33";
    char *msg_5 = "$GLGSV,3,1,11,65,47,150,40,66,42,130,40,67,37,044,34,68,29,343,33";
    char *msg_6 = "$BDGSV,3,1,11,134,48,153,40,135,43,134,36,137,47,211,40,138,46,037,38";
    char *msg_7 = "$GPGLL,4916.45,N,12311.12,W,225444,A,*1D";

    // Action & Assertion
    TEST_ASSERT_EQUAL(0x69, NMEA_calculateCRC(msg_1));
    TEST_ASSERT_EQUAL(0x39, NMEA_calculateCRC(msg_2));
    TEST_ASSERT_EQUAL(0x44, NMEA_calculateCRC(msg_3));
    TEST_ASSERT_EQUAL(0x7F, NMEA_calculateCRC(msg_4));
    TEST_ASSERT_EQUAL(0x64, NMEA_calculateCRC(msg_5));
    TEST_ASSERT_EQUAL(0x67, NMEA_calculateCRC(msg_6));
    TEST_ASSERT_EQUAL(0x1D, NMEA_calculateCRC(msg_7));
}


void test_retrieveCRC_Valid()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";
    char *msg_2 = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    char *msg_3 = "$GPRMC,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*44";
    char *msg_4 = "$GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7f";
    char *msg_5 = "$GLGSV,3,1,11,65,47,150,40,66,42,130,40,67,37,044,34,68,29,343,33*64\r\n";
    char *msg_6 = "$BDGSV,3,1,11,134,48,153,40,135,43,134,36,137,47,211,40,138,46,037,38*67\r\n";
    char *msg_7 = "$GPGLL,4916.45,N,12311.12,W,225444,A,*1D";

    // Action & Assertion
    TEST_ASSERT_EQUAL(0x69, NMEA_retrieveCRC(msg_1));
    TEST_ASSERT_EQUAL(0x39, NMEA_retrieveCRC(msg_2));
    TEST_ASSERT_EQUAL(0x44, NMEA_retrieveCRC(msg_3));
    TEST_ASSERT_EQUAL(0x7F, NMEA_retrieveCRC(msg_4));
    TEST_ASSERT_EQUAL(0x64, NMEA_retrieveCRC(msg_5));
    TEST_ASSERT_EQUAL(0x67, NMEA_retrieveCRC(msg_6));
    TEST_ASSERT_EQUAL(0x1D, NMEA_retrieveCRC(msg_7));
}

void test_retrieveCRC_Valid_NoStartChar()
{
    // Preparation
    char *message = "GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";

    // Action
    uint16_t checksum = NMEA_retrieveCRC(message);

    // Assertion
    TEST_ASSERT_EQUAL(0x69, checksum);
}

void test_retrieveCRC_Invalid_UncorrectHexCharacter()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*6G";
    char *msg_2 = "$GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*lw";

    // Action & Assertion
    TEST_ASSERT_EQUAL(0x00, NMEA_retrieveCRC(msg_1));
    TEST_ASSERT_EQUAL(0x00, NMEA_retrieveCRC(msg_2));
}

void test_retrieveCRC_Invalid_NoCRCvalue()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*";

    // Action & Assertion
    TEST_ASSERT_EQUAL(0x00, NMEA_retrieveCRC(msg_1));
}

void test_retrieveCRC_Invalid_NoControlChar()
{
    // Preparation
    char *message = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,69";

    // Action
    uint16_t checksum = NMEA_retrieveCRC(message);

    // Assertion
    TEST_ASSERT_EQUAL(0x00, checksum);
}

void test_retrieveCRC_Invalid_NullMessagePointer()
{
    // Preparation
    char *message = (char*) malloc(32 * sizeof(char));

    // Action
    uint16_t checksum = NMEA_retrieveCRC(message);

    // Assertion
    TEST_ASSERT_EQUAL(0x00, checksum);

    // Clean up
    free(message);
}

void test_retrieveCRC_Invalid_MessageTooShort()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*6";
    char *msg_2 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*";

    // Action & Assertion
    TEST_ASSERT_EQUAL(0x00, NMEA_retrieveCRC(msg_1));
    TEST_ASSERT_EQUAL(0x00, NMEA_retrieveCRC(msg_2));
}


void test_checkCRC_Valid()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*69";
    char *msg_2 = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    char *msg_3 = "$GPRMC,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*44";
    char *msg_4 = "GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7F";
    char *msg_5 = "GLGSV,3,1,11,65,47,150,40,66,42,130,40,67,37,044,34,68,29,343,33*64";
    char *msg_6 = "$BDGSV,3,1,11,134,48,153,40,135,43,134,36,137,47,211,40,138,46,037,38*67\r\n";
    char *msg_7 = "$GPGLL,4916.45,N,12311.12,W,225444,A,*1D";

    // Action & Assertion
    TEST_ASSERT_TRUE(NMEA_checkCRC(msg_1));
    TEST_ASSERT_TRUE(NMEA_checkCRC(msg_2));
    TEST_ASSERT_TRUE(NMEA_checkCRC(msg_3));
    TEST_ASSERT_TRUE(NMEA_checkCRC(msg_4));
    TEST_ASSERT_TRUE(NMEA_checkCRC(msg_5));
    TEST_ASSERT_TRUE(NMEA_checkCRC(msg_6));
    TEST_ASSERT_TRUE(NMEA_checkCRC(msg_7));
}

void test_checkCRC_Invalid()
{
    // Preparation
    char *msg_1 = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*48";
    char *msg_2 = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*3";
    char *msg_3 = "$GPRMC,123519.00,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W44";
    char *msg_4 = "$GPGSV,3,1,11,05,63,079,32,09,54,261,41,12,25,088,32,15,65,302,33*7H";

    // Action & Assertion
    TEST_ASSERT_FALSE(NMEA_checkCRC(msg_1));
    TEST_ASSERT_FALSE(NMEA_checkCRC(msg_2));
    TEST_ASSERT_FALSE(NMEA_checkCRC(msg_3));
    TEST_ASSERT_FALSE(NMEA_checkCRC(msg_4));
}

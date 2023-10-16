#include <unity.h>
#include "led/led.h"

static uint8_t reg = 0x22;
static uint8_t port = 0x16;
static uint8_t pin = 2;

void test_LedCreate()
{
    // Preparation
    LED_T *led = (LED_T*) malloc(sizeof(LED_T));

    // Action
    LedCreate(led, &reg, &port, pin);

    // Assertion
    TEST_ASSERT_EQUAL(&reg,     led->reg);
    TEST_ASSERT_EQUAL(&port,    led->port);
    TEST_ASSERT_EQUAL(pin,      led->pin);
    TEST_ASSERT_EQUAL(LED_OFF,  led->state);

    // Clean up
    free(led);
}

void test_LedOn()
{
    // Preparation
    LED_T led = {LED_OFF, &reg, &port, pin};

    // Action
    LedOn(&led);

    // Assertion
    TEST_ASSERT_EQUAL(LED_ON, led.state);
}

void test_LedOff()
{
    // Preparation
    LED_T led = {LED_ON, &reg, &port, pin};

    // Action
    LedOff(&led);

    // Assertion
    TEST_ASSERT_EQUAL(LED_OFF, led.state);
}

void test_LedToogle()
{
    // Preparation
    LED_T led1 = {LED_ON, &reg, &port, pin};
    LED_T led2 = {LED_OFF, &reg, &port, pin};

    // Action
    LedToogle(&led1);
    LedToogle(&led2);

    // Assertion
    TEST_ASSERT_EQUAL(LED_OFF, led1.state);
    TEST_ASSERT_EQUAL(LED_ON, led2.state);
}

void test_LedSetState()
{
    // Preparation
    LED_T led1 = {LED_ON, &reg, &port, pin};
    LED_T led2 = {LED_OFF, &reg, &port, pin};

    // Action
    LedSetState(&led1, LED_OFF);
    LedSetState(&led2, LED_ON);

    // Assertion
    TEST_ASSERT_EQUAL(LED_OFF, led1.state);
    TEST_ASSERT_EQUAL(LED_ON, led2.state);
}

void test_LedGetState()
{
    // Preparation
    LED_T led1 = {LED_ON, &reg, &port, pin};
    LED_T led2 = {LED_OFF, &reg, &port, pin};

    // Action & Assertion
    TEST_ASSERT_EQUAL(LED_ON,  LedGetState(&led1));
    TEST_ASSERT_EQUAL(LED_OFF, LedGetState(&led2));
}

void test_LedDestroy()
{
    // Preparation
    LED_T *led1 = (LED_T*) malloc(sizeof(LED_T));
    LED_T *led2 = NULL;
    LED_T ptr = *led1;

    // Action
    LedDestroy(led1);
    LedDestroy(led2);

    // Assertion
    TEST_ASSERT_NOT_EQUAL(&ptr, led1);
    TEST_ASSERT_EQUAL(NULL, led2);
}

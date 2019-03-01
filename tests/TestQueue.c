#include "unity.h"
#include "Queue.h"

#define QUEUESIZEUINT8      sizeof(uint8_t) * 10
#define QUEUESIZEUINT16     sizeof(uint16_t) * 10
#define QUEUESIZEUINT32     sizeof(uint32_t) * 10
#define QUEUESIZEINT16      sizeof(int16_t) * 10
#define QUEUESIZEINT32      sizeof(int32_t) * 10
#define QUEUESIZEFLOAT      sizeof(float) * 10

static uint8_t error;
static queue_array_t queue_array_uint8[QUEUESIZEUINT8] = {0};
static queue_array_t queue_array_uint16[QUEUESIZEUINT16] = {0};
static queue_array_t queue_array_uint32[QUEUESIZEUINT32] = {0};
static queue_array_t queue_array_int16[QUEUESIZEINT16] = {0};
static queue_array_t queue_array_int32[QUEUESIZEINT32] = {0};
static queue_array_t queue_array_float[QUEUESIZEFLOAT] = {0};
static queue_t queue_uint8;
static queue_t queue_uint16;
static queue_t queue_uint32;
static queue_t queue_int16;
static queue_t queue_int32;
static queue_t queue_float;

void
setUp(void)
{
    error = 0;

    queue_init(&queue_uint8,
               queue_array_uint8,
               QUEUESIZEUINT8,
               sizeof(uint8_t));

    queue_init(&queue_uint16,
               queue_array_uint16,
               QUEUESIZEUINT16,
               sizeof(uint16_t));

    queue_init(&queue_uint32,
               queue_array_uint32,
               QUEUESIZEUINT32, 
               sizeof(uint32_t));

    queue_init(&queue_int16,
               queue_array_int16,
               QUEUESIZEINT16,
               sizeof(int16_t));

    queue_init(&queue_int32,
               queue_array_int32,
               QUEUESIZEINT32, 
               sizeof(int32_t));

    queue_init(&queue_float,
               queue_array_float,
               QUEUESIZEFLOAT, 
               sizeof(float));
}

void
tearDown(void)
{

}

void
test_Queue_should_BehaveAsFIFO(void)
{
    const uint8_t data[5] = {10, 20, 30, 40, 50};
    uint8_t ret;
    uint8_t i;

    for (i = 0; i < 5; i++)
    {
        queue_enqueue(&queue_uint8, (void *) &data[i]);
    }

    for (i = 0; i < 5; i++)
    {
        error = queue_dequeue(&queue_uint8, &ret);
        TEST_ASSERT_EQUAL_UINT8(data[i], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }
}

void
test_Queue_should_BehaveAsCircularFIFO(void)
{
    const uint8_t data[11] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
    uint8_t ret;
    uint8_t i;

    for (i = 0; i < 10; i++)
    {
        error = queue_enqueue(&queue_uint8, (void *) &data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    error = queue_dequeue(&queue_uint8, &ret);
    TEST_ASSERT_EQUAL_UINT8(data[0], ret);
    TEST_ASSERT_EQUAL_UINT8(0, error);

    error = queue_enqueue(&queue_uint8, (void *) &data[10]);
    TEST_ASSERT_EQUAL_UINT8(0, error);

    for (i = 0; i < 10; i++)
    {
        error = queue_dequeue(&queue_uint8, &ret);
        TEST_ASSERT_EQUAL_UINT8(data[i + 1], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }
}

void
test_Queue_should_IndicateUnderflow(void)
{
    const uint8_t data[5] = {10, 20, 30, 40, 50};
    uint8_t ret;
    uint8_t i;

    for (i = 0; i < 5; i++)
    {
        error = queue_enqueue(&queue_uint8, (void *) &data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    for (i = 0; i < 5; i++)
    {
        error = queue_dequeue(&queue_uint8, &ret);
        TEST_ASSERT_EQUAL_UINT8(data[i], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    error = queue_dequeue(&queue_uint8, &ret);
    TEST_ASSERT_EQUAL_UINT8(1, error);
}

void
test_Queue_should_IndicateOverflow(void)
{
    const uint8_t data[11] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
    uint8_t i;

    for (i = 0; i < 10; i++)
    {
        error = queue_enqueue(&queue_uint8, (void *) &data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    error = queue_enqueue(&queue_uint8, (void *) &data[10]);
    TEST_ASSERT_EQUAL_UINT8(1, error);
}

void
test_Queue_should_WorkWithUint16(void)
{
    const uint16_t data[5] = {100, 200, 300, 400, 500};
    uint16_t ret;
    uint8_t i;

    for (i = 0; i < 5; i++)
    {
        error = queue_enqueue(&queue_uint16, (void *) &data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    for (i = 0; i < 5; i++)
    {
        error = queue_dequeue(&queue_uint16, &ret);
        TEST_ASSERT_EQUAL_UINT16(data[i], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }
}

void
test_Queue_should_WorkWithUint32(void)
{
    const uint32_t data[5] = {70000, 80000, 90000, 100000, 4294967295};
    uint32_t ret;
    uint8_t i;

    for (i = 0; i < 5; i++)
    {
        error = queue_enqueue(&queue_uint32, (void *) &data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    for (i = 0; i < 5; i++)
    {
        error = queue_dequeue(&queue_uint32, &ret);
        TEST_ASSERT_EQUAL_UINT32(data[i], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }
}

void
test_Queue_should_WorkWithInt16(void)
{
    const int16_t data[5] = {-100, 200, -300, 400, -500};
    int16_t ret;
    uint8_t i;

    for (i = 0; i < 5; i++)
    {
        error = queue_enqueue(&queue_int16, (void *) &data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    for (i = 0; i < 5; i++)
    {
        error = queue_dequeue(&queue_int16, &ret);
        TEST_ASSERT_EQUAL_INT16(data[i], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }
}

void
test_Queue_should_WorkWithInt32(void)
{
    const int32_t data[5] = {-70000, 80000, -90000, 100000, -42949672};
    int32_t ret;
    uint8_t i;

    for (i = 0; i < 5; i++)
    {
        error = queue_enqueue(&queue_int32, (void *) &data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    for (i = 0; i < 5; i++)
    {
        error = queue_dequeue(&queue_int32, &ret);
        TEST_ASSERT_EQUAL_INT32(data[i], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }
}

void
test_Queue_should_WorkWithFloat(void)
{
    const float data[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float ret;
    uint8_t i;

    for (i = 0; i < 5; i++)
    {
        error = queue_enqueue(&queue_float, (void *) &data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    for (i = 0; i < 5; i++)
    {
        error = queue_dequeue(&queue_float, &ret);
        TEST_ASSERT_EQUAL_FLOAT(data[i], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }
}

void
test_Queue_should_WorkWithStrings(void)
{
    const char *data[] = {
        "0x0001",
        "0x0002",
        "0x0003",
    };
    char ret[7];
    queue_array_t queue_array_string[sizeof(data[0]) * 3] = {0};
    queue_t queue_string;
    uint8_t error;
    uint8_t i;

    queue_init(&queue_string,
               queue_array_string,
               sizeof(data[0]) * 3,
               sizeof(data[0]));

    for (i = 0; i < 3; i++)
    {
        error = queue_enqueue(&queue_string, (void *) data[i]);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }

    error = queue_enqueue(&queue_string, (void *) data[0]);
    TEST_ASSERT_EQUAL_UINT8(1, error);

    for (i = 0; i < 3; i++)
    {
        error = queue_dequeue(&queue_string, &ret);
        TEST_ASSERT_EQUAL_STRING(data[i], ret);
        TEST_ASSERT_EQUAL_UINT8(0, error);
    }
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Queue_should_BehaveAsFIFO);
    RUN_TEST(test_Queue_should_BehaveAsCircularFIFO);
    RUN_TEST(test_Queue_should_IndicateUnderflow);
    RUN_TEST(test_Queue_should_IndicateOverflow);
    RUN_TEST(test_Queue_should_WorkWithUint16);
    RUN_TEST(test_Queue_should_WorkWithUint32);
    RUN_TEST(test_Queue_should_WorkWithInt16);
    RUN_TEST(test_Queue_should_WorkWithInt32);
    RUN_TEST(test_Queue_should_WorkWithFloat);
    RUN_TEST(test_Queue_should_WorkWithStrings);
    return UNITY_END();
}
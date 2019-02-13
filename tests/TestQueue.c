#include "unity.h"
#include "Queue.h"

static int ret;
static queue_t queue;

void
setUp(void)
{
    ret = 0;
    queue_init(&queue);
}

void
tearDown(void)
{

}

void
test_Queue_should_BehaveAsFIFO(void)
{
    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);
    queue_enqueue(&queue, 30);
    queue_enqueue(&queue, 40);
    queue_enqueue(&queue, 50);

    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(10, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(20, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(30, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(40, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(50, ret);
}

void
test_Queue_should_BehaveAsCircularFIFO(void)
{
    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);
    queue_enqueue(&queue, 30);
    queue_enqueue(&queue, 40);
    queue_enqueue(&queue, 50);
    queue_enqueue(&queue, 60);
    queue_enqueue(&queue, 70);
    queue_enqueue(&queue, 80);
    queue_enqueue(&queue, 90);
    queue_enqueue(&queue, 100);

    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(10, ret);

    queue_enqueue(&queue, 110);

    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(20, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(30, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(40, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(50, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(60, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(70, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(80, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(90, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(100, ret);
    queue_dequeue(&queue, &ret);
    TEST_ASSERT_EQUAL_HEX8(110, ret);
}

void
test_Queue_should_IndicateUnderflow(void)
{
    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);
    queue_enqueue(&queue, 30);
    queue_enqueue(&queue, 40);
    queue_enqueue(&queue, 50);

    queue_dequeue(&queue, &ret);
    queue_dequeue(&queue, &ret);
    queue_dequeue(&queue, &ret);
    queue_dequeue(&queue, &ret);
    
    TEST_ASSERT_EQUAL_HEX8(0, queue_dequeue(&queue, &ret));
    TEST_ASSERT_EQUAL_HEX8(-1, queue_dequeue(&queue, &ret));
}

void
test_Queue_should_IndicateOverflow(void)
{
    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);
    queue_enqueue(&queue, 30);
    queue_enqueue(&queue, 40);
    queue_enqueue(&queue, 50);
    queue_enqueue(&queue, 60);
    queue_enqueue(&queue, 70);
    queue_enqueue(&queue, 80);
    queue_enqueue(&queue, 90);

    TEST_ASSERT_EQUAL_HEX8(0, queue_enqueue(&queue, 100));
    TEST_ASSERT_EQUAL_HEX8(-1, queue_enqueue(&queue, 110));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Queue_should_BehaveAsFIFO);
    RUN_TEST(test_Queue_should_BehaveAsCircularFIFO);
    RUN_TEST(test_Queue_should_IndicateUnderflow);
    RUN_TEST(test_Queue_should_IndicateOverflow);
    return UNITY_END();
}
#include "tqueue.h"

#include <gtest.h>

TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> queue(5));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(TQueue<int> queue(-5));
}

TEST(TQueue, can_create_copied_queue)
{
	TQueue<int> queue(10);

	ASSERT_NO_THROW(TQueue<int> queue1(queue));
}

TEST(TQueue, can_set_and_get_element)
{
	TQueue<int> queue(4);
	queue.push(1);

	EXPECT_EQ(1, queue.pop());
}

TEST(TQueue, queue_is_empty)
{
	TQueue<int> queue(4);

	EXPECT_TRUE(queue.isEmpty());
}

TEST(TQueue, queue_is_full)
{
	TQueue<int> queue(3);
	queue.push(1);
	queue.push(2);

	EXPECT_TRUE(queue.isFull());
}






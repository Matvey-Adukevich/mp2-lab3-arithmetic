#include "tstack.h"

#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> stack(5));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> stack(10);
	stack.push(1);
	stack.push(2);

	ASSERT_NO_THROW(TStack<int> stack1(stack));
}

TEST(TStack, is_empty)
{
	TStack<int> stack(5);

	EXPECT_TRUE(stack.isEmpty());
}

TEST(TStack, is_full)
{
	TStack<int> stack(2);
	stack.push(1);
	stack.push(2);

	EXPECT_TRUE(stack.isFull());
}

TEST(TStack, can_set_and_get_element)
{
	TStack<int> stack(4);
	stack.push(1);

	EXPECT_EQ(1, stack.pop());
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> stack(5);
	stack.push(1);
	stack.push(2);
	ASSERT_NO_THROW(stack = stack);
}


TEST(TStack, can_get_top)
{
	TStack<int> stack(4);
	stack.push(1);
	stack.push(2);
	EXPECT_EQ(2, stack.top());
}

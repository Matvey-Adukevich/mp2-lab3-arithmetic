#include "TArithmeticExpression.h"

#include <gtest.h>

TEST(TArithmeticExpression, correct)
{
	ASSERT_NO_THROW(TArithmeticExpression expr("(12+32)*4"));
}
TEST(TArithmeticExpression, correct_un_ops)
{
	ASSERT_NO_THROW(TArithmeticExpression expr("(-12)*4"));
}

TEST(TArithmeticExpression, double_plus)
{
	ASSERT_ANY_THROW(TArithmeticExpression expr("(12++32)*4"));
}

TEST(TArithmeticExpression, no_operator)
{
	ASSERT_ANY_THROW(TArithmeticExpression expr("(12+32)4"));
}

TEST(TArithmeticExpression, no_open_bracket)
{
	ASSERT_ANY_THROW(TArithmeticExpression expr("12+32)*4"));
}

TEST(TArithmeticExpression, no_close_bracket)
{
	ASSERT_ANY_THROW(TArithmeticExpression expr("(12+32*4"));
}

TEST(TArithmeticExpression, brackets)
{
	ASSERT_ANY_THROW(TArithmeticExpression expr("()"));
}

TEST(TArithmeticExpression, double_operator_and_branch)
{
	ASSERT_ANY_THROW(TArithmeticExpression expr("(12+32*)*4"));
}

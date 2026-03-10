#include <gtest/gtest.h>
#include "Token.hpp"

// test_suite_name, test_name
// Operator Precedence Test. (Ranking) 
// Binary Operator Test.
// Every Binary Operator has defined BinOp
// sizeof(kTokenAttributes == ETokenTypes::_MAX_)
TEST(TokenzierTest, OperatorPrecedence)
{
    EXPECT_EQ(1 + 1, 2);
}

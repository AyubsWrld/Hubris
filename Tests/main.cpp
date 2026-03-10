#include <gtest/gtest.h>
#include "Token.hpp"

// test_suite_name, test_name
// Operator Precedence Test. (Ranking) 
// Binary Operator Test.
// Every Binary Operator has defined BinOp
// sizeof(kTokenAttributes == ETokenTypes::_MAX_)

// Used structs so there isn't all a need for access specifiers most attributes should be public anyway.
struct TokenTest : public testing::Test
{
    const FToken& Addition = GetTokenAttributes(ETokenType::PlusMinus);
    const FToken& Subtraction = GetTokenAttributes(ETokenType::PlusMinus);
};

TEST_F(TokenTest, OperatorPrecedence)
{
    EXPECT_EQ(Addition.BinOp, Subtraction.BinOp) << "Addition && Subtraction should have the same operator precedence";
}


int main (int argc, char *argv[]) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



#pragma once
#include <gtest/gtest.h>
#include "Token.hpp"

// (1) Operator Precedence Test. (Ranking) 

// (2) Binary Operator Test.

// (3) Every Binary Operator has defined BinOp

// (4) sizeof(kTokenAttributes == ETokenTypes::_MAX_)

// (5) Used structs so there isn't all a need for access specifiers most attributes should be public anyway.

struct TokenTest : public testing::Test
{
    const FToken& Addition = GetTokenAttributes(ETokenType::PlusMinus);
    const FToken& Subtraction = GetTokenAttributes(ETokenType::PlusMinus);
    const FToken& Pipeline = GetTokenAttributes(ETokenType::Pipeline);
    const FToken& NullishCoalescing = GetTokenAttributes(ETokenType::NullishCoalescing);
    const FToken& LogicalOR = GetTokenAttributes(ETokenType::LogicalOR);
    const FToken& LogicalAND = GetTokenAttributes(ETokenType::LogicalAND);
    const FToken& BitwiseOR = GetTokenAttributes(ETokenType::BitwiseOR);
    const FToken& BitwiseXOR = GetTokenAttributes(ETokenType::BitwiseXOR);
    const FToken& BitwiseAND = GetTokenAttributes(ETokenType::BitwiseAND);
    const FToken& Equality = GetTokenAttributes(ETokenType::Equality);
    const FToken& LessThan = GetTokenAttributes(ETokenType::LessThan);
    const FToken& GreaterThan = GetTokenAttributes(ETokenType::GreaterThan);
    const FToken& Relational = GetTokenAttributes(ETokenType::Relational);
    const FToken& BitShift = GetTokenAttributes(ETokenType::BitShift);
    const FToken& BitShiftLeft = GetTokenAttributes(ETokenType::BitShiftLeft);
    const FToken& BitShiftRight = GetTokenAttributes(ETokenType::BitShiftRight);
    const FToken& PlusMinus = GetTokenAttributes(ETokenType::PlusMinus);
    const FToken& Modulo = GetTokenAttributes(ETokenType::Modulo);
    const FToken& Star = GetTokenAttributes(ETokenType::Star);
    const FToken& Slash = GetTokenAttributes(ETokenType::Slash);
    const FToken& Exponent = GetTokenAttributes(ETokenType::Exponent);
};

TEST_F(TokenTest, BinaryOperatorTest)
{
    // (1) Should all be operators. 
    for (const FToken* Token : {
        &Pipeline, &NullishCoalescing, &LogicalOR, &LogicalAND,
        &BitwiseOR, &BitwiseXOR, &BitwiseAND, &Equality,
        &LessThan, &GreaterThan, &Relational, &BitShift,
        &BitShiftLeft, &BitShiftRight, &PlusMinus, &Modulo,
        &Star, &Slash, &Exponent
    }) {
        EXPECT_TRUE(Token->IsBinaryOperator());
    }

}

TEST_F(TokenTest, AssociativityTest)
{
    // (2) Associativity Checks, All binary operators should left associative except **.

    for (const FToken* Token : {
        &Pipeline, &NullishCoalescing, &LogicalOR, &LogicalAND,
        &BitwiseOR, &BitwiseXOR, &BitwiseAND, &Equality,
        &LessThan, &GreaterThan, &Relational, &BitShift,
        &BitShiftLeft, &BitShiftRight, &PlusMinus, &Modulo,
        &Star, &Slash, &Exponent
    }) {
         if ( Token->TokenType != ETokenType::Exponent )
         {
            EXPECT_FALSE(Token->IsRightAssociative());
         } 
         else 
         {
            EXPECT_TRUE(Token->IsRightAssociative());
         }
    }
}

TEST_F(TokenTest, FixityTest)
{
    // (3) Checks Operators Fixity.

    for (const FToken* Token : {
        &Pipeline, &NullishCoalescing, &LogicalOR, &LogicalAND,
        &BitwiseOR, &BitwiseXOR, &BitwiseAND, &Equality,
        &LessThan, &GreaterThan, &Relational, &BitShift,
        &BitShiftLeft, &BitShiftRight, &PlusMinus, &Modulo,
        &Star, &Slash, &Exponent
    }) 
    {
    }
}

TEST_F(TokenTest, KeywordTests)
{
}

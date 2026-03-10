#pragma once
#include "Token.hpp"
#include "Construction.hpp";
#include <utility>
#include <optional>

constexpr bool FToken::IsIdentifier() const noexcept
{
    return TokenType >= ETokenType::As && TokenType >= ETokenType::Placeholder;
}

constexpr bool FToken::KeywordOrIdentifierIsKeyword() const noexcept
{
    return TokenType <= ETokenType::While;
}

constexpr bool FToken::IsKeywordOrIdentifier() const noexcept
{
    return TokenType >= ETokenType::In && TokenType <= ETokenType::Placeholder;
}

constexpr bool FToken::IsLiteralPropertyName() const noexcept
{
    return TokenType >= ETokenType::In && TokenType <= ETokenType::BigInt;
}


constexpr bool FToken::PrefixesExpression() const noexcept
{
    return Flags.BeforeExpr;
}

constexpr bool FToken::CanStartExpression() const noexcept
{
    return Flags.StartsExpr;
}

constexpr bool FToken::IsAssignment() const noexcept
{
    return TokenType >= ETokenType::Eq && TokenType <= ETokenType::ModuloAssign;
}
constexpr bool FToken::IsFlowInterfaceOrTypeOrOpaque() const noexcept
{
    return TokenType >= ETokenType::Interface && TokenType <= ETokenType::Opaque;
}
constexpr bool FToken::IsLoop() const noexcept
{
    return TokenType >= ETokenType::Do && TokenType <= ETokenType::While;
}

constexpr bool FToken::IsKeyword() const noexcept
{
    return TokenType >= ETokenType::In && TokenType <= ETokenType::While;
}

constexpr bool FToken::IsOperator() const noexcept
{
    return TokenType >= ETokenType::Pipeline && TokenType <= ETokenType::Instanceof;
}
constexpr bool FToken::IsPostfix() const noexcept
{
    return Flags.Postfix;
}
constexpr bool FToken::IsPrefix() const noexcept
{
    return Flags.Prefix;
}
constexpr bool FToken::IsTSTypeOperator() const noexcept
{
    return TokenType >= ETokenType::Keyof && TokenType <= ETokenType::Unique;
}
constexpr bool FToken::IsTSDeclarationStart() const noexcept
{
    return TokenType >= ETokenType::Abstract && TokenType <= ETokenType::Type;
}
constexpr bool FToken::IsRightAssociative() const noexcept
{
    return Flags.RightAssociative;
}

constexpr bool FToken::IsBinaryOperator() const noexcept
{
    // This reads better than the explicit operator bool() defined on std::optional. 
    return BinOp.has_value();
}

constexpr std::optional<U8> FToken::OperatorPrecedence() const noexcept
{
    return BinOp;
}

const FToken& GetTokenAttributes(ETokenType InToken)
{
    return kTokenAttributes[std::to_underlying(InToken)];
}

#pragma once
#include "Token.hpp"
#include "Construction.hpp";

constexpr bool FToken::IsIdentifier() const noexcept
{
    STUB_INVOCATION();
    return false;
}

constexpr bool FToken::KeywordOrIdentifierIsKeyword() const noexcept
{
    STUB_INVOCATION();
    return false;
}

constexpr bool FToken::IsLiteralPropertyName() const noexcept
{
    STUB_INVOCATION();
    return false;
}

constexpr bool FToken::PrefixesExpression() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsAssignment() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsFlowInterfaceOrTypeOrOpaque() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsLoop() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsOperator() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsPostfix() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsPrefix() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsTSTypeOperator() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsTSDeclarationStart() const noexcept
{
    STUB_INVOCATION();
    return false;
}
constexpr bool FToken::IsRightAssociative() const noexcept
{
    STUB_INVOCATION();
    return false;
}

constexpr bool FToken::operator==(const FToken& other) const
{
    STUB_INVOCATION();
    return false;
}

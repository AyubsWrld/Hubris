#pragma once
#include "Context.hpp"

FTokenContext::FTokenContext(std::string InToken, bool bInPreserveSpace)
{
    Token = InToken;
    bPreserveSpace = bInPreserveSpace;
}


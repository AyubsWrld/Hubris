#pragma once
#include <string>

struct FTokenContext
{
    std::string     Token;
    bool            bPreserveSpace;


    FTokenContext(const FTokenContext&) = default;
    FTokenContext& operator=(const FTokenContext&) = default;

    FTokenContext(FTokenContext&&) = default;
    FTokenContext& operator=(FTokenContext&&) = default;

    FTokenContext(std::string, bool);

};

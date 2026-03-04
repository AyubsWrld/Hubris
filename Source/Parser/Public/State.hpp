#pragma once 
#include "ShorthandTypes.hpp"
#include "SourceLocation.hpp"

class FState 
{
    U64 StartIndex;
    U64 CurrentLine;
    U64 LineStart;

    FPosition StartLocation;
    FPosition EndLocation;
};

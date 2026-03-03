#pragma once 
#include <optional>
#include "ShorthandTypes.hpp"


/* Represents source position */
struct FPosition 
{
    U64     Line;
    U64     Column;
    U64     Index;
};

struct FSourceLocation 
{
    FPosition                   Start;
    FPosition                   End;
    std::string                 Filename;
    std::optional<std::string>  IdentifierName;
};

/*
   @purpose:            Creates a new FPosition with a non-zero column offset applied
                        to the given position. Intended for use when constructing AST
                        nodes from token boundaries where the column must be adjusted
                        without modifying line or index information. This function
                        does not skip or account for whitespace.

   @param:              [in]                    const FPosition& pos
                                                Base position to offset.

   @param:              [in]                    U64 offset
                                                Column offset to apply.

                                       return

   @code:               FPosition               New position with adjusted column value.

   @notes:              Line and Index fields remain unchanged.
                        Column is incremented by the specified offset.
                        noexcept guarantee — does not throw exceptions.

*/
inline FPosition CreatePositionWithColumnOffset(const FPosition& pos, U64 offset) noexcept
{
    return FPosition {
        .Line   = pos.Line,
        .Column = pos.Column + offset,
        .Index  = pos.Index
    };
};

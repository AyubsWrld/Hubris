#pragma once
#include "ShorthandTypes.hpp"
#include <type_traits>

// How to better model this representation
enum class ECommentType 
{
    CommentBlock,
    CommentLine,
    _MAX_
};

class FCommentBase 
{

public:
    const   FString         Value;
    const   U64             Start;
    const   U64             End;
};

class FCommentBlock : public FCommentBase
{
    const   ECommentType    Type { ECommentType::CommentBlock };
};

class FCommentLine : public FCommentBase
{
    const   ECommentType    Type { ECommentType::CommentBlock };
};




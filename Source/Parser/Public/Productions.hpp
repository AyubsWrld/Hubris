#pragma once
#include "ShorthandTypes.hpp"
#include <type_traits>

// How to better model this representation

/* --------------------------------------------------------------[ Comments ]-------------------------------------------------------------------- */

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


struct FCommentWhitespace
{ 
    U64     Start;
    U64     End;
};

/* --------------------------------------------------------------[ Comments ]-------------------------------------------------------------------- */
/* --------------------------------------------------------------[ Nodebase ]-------------------------------------------------------------------- */

struct NodeBase
{
    U64     Start;
    U64     End;
};


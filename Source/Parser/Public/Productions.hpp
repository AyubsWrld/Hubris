#pragma once
#include "ShorthandTypes.hpp"
#include "SourceLocation.hpp"
#include <optional>
#include <type_traits>

// How to better model this representation

/* --------------------------------------------------------------[ Comments ]-------------------------------------------------------------------- */

struct  FComment;
struct  FNodeBase;
struct  NodeBase;
struct  FCommentWhitespace;

using   Comments    =   std::vector<FComment>;

enum class ECommentType 
{
    CommentBlock,
    CommentLine,
    _MAX_
};

struct FComment
{
    const   ECommentType    Type ;
    const   FString         Value;
    const   U64             Start;
    const   U64             End;
};

struct FNodeBase
{
    const       U64                 Start;
    const       U64                 End;
    const       FSourceLocation     Location;
    const       NumericRange        Range;
};

/* A whitespace containing comments */


struct FCommentWhitespace
{
    const       U64             Start;
    const       U64             End;
    Comments                    CommentMembers;
    const       ECommentType    Type ;
    const       FString         Value;
};



/* --------------------------------------------------------------[ Comments ]-------------------------------------------------------------------- */
/* --------------------------------------------------------------[ Nodebase ]-------------------------------------------------------------------- */

struct NodeBase
{
    const   U64             Start;
    const   U64             End;
    const   NumericRange    Range;
    const   Comments        LeadingComments;
    const   Comments        TrailingComments;
    const   Comments        Innercomments;

    const   std::optional<void*> Extras; // reasoning?
};

/*

type NodeAny<T extends string, KnownProps = object> = NodeBase & {
  type: T;
  [key: string]: any;
} & KnownProps;

*/

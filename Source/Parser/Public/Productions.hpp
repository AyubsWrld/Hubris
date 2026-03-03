#pragma once
#include "ShorthandTypes.hpp"
#include "SourceLocation.hpp"
#include <optional>
#include <type_traits>
#include <variant>
#include <concepts>
#include <vector>


struct  FComment;
struct  FCommentWhitespace;
using   Comments    =   std::vector<FComment>;

/* --------------------------------------------------------------[ Enums ]------------------------------------------------------------------- */

enum class ECommentType 
{
    CommentBlock,
    CommentLine,
    _MAX_
};

enum class EAssignmentOperator
{
    Assign,                     // =
    AddAssign,                  // +=
    SubtractAssign,             // -=
    MultiplyAssign,             // *=
    DivideAssign,               // /=
    ModuloAssign,               // %=
    LeftShiftAssign,            // <<=
    RightShiftAssign,           // >>=
    UnsignedRightShiftAssign,   // >>>=
    BitwiseOrAssign,            // |=
    BitwiseXorAssign,           // ^=
    BitwiseAndAssign,           // &=
    LogicalAndAssign,           // &&=
    LogicalOrAssign,            // ||=
    NullishCoalescingAssign     // ??=
};

enum class EUnaryOperator
{
    Subraction,     // -
    Addition,       // +
    LogicalNot,     // !
    BitwiseNot,     // ~
    TypeOf,         // typeof
    Void,           // void
    Delete,         // delete
    Throw,          // throw
    _MAX_
};

enum class EBinaryOperator
{
    Equal,                  // ==
    NotEqual,               // !=
    StrictEqual,            // ===
    StrictNotEqual,         // !==
    LessThan,               // <
    LessThanOrEqual,        // <=
    GreaterThan,            // >
    GreaterThanOrEqual,     // >=
    LeftShift,              // <<
    RightShift,             // >>
    UnsignedRightShift,     // >>>
    Addition,               // +
    Subtraction,            // -
    Multiplication,         // *
    Division,               // /
    Modulo,                 // %
    BitwiseOr,              // |
    BitwiseXor,             // ^
    BitwiseAnd,             // &
    In,                     // in
    InstanceOf,             // instanceof
    _MAX_
};

enum class EUpdateOperator
{
    Increment,  // ++
    Decrement   // --
};

/* --------------------------------------------------------------[ Enums ]----------------------------------------------------------------------- */

/* --------------------------------------------------------------[ Comments ]-------------------------------------------------------------------- */

struct FComment
{
    const   ECommentType    Type ;
    const   FString         Value;
    const   U64             Start;
    const   U64             End;
};

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

struct FNodeBase
{
    const   U64             Start;
    const   U64             End;
    const   NumericRange    Range;
    const   Comments        LeadingComments;
    const   Comments        TrailingComments;
    const   Comments        Innercomments;
    const   std::optional<void*> Extras; // reasoning?
};

/* --------------------------------------------------------------[ Nodebase ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ Statements ]-------------------------------------------------------------------- */

struct FStatement : public FNodeBase { }; 

template<typename T>
constexpr bool IsStatment = std::is_base_of_v<FStatement, T>;

template<typename T>
concept Statement = requires(T a){ IsStatment<T>; };

struct FBlockStatement 
{
    std::vector<FStatement> Body;
};

/* --------------------------------------------------------------[ Statements ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ Expressions ]-------------------------------------------------------------------- */


struct FAssignmentExpression;
struct FBinaryExpression;
struct FCallExpression;
struct FConditionalExpression;
struct FFunctionExpression;
struct FIdentifier;
struct FStringLiteral;
struct FNumericLiteral;
struct FNullLiteral;
struct FBooleanLiteral;
struct FRegExpLiteral;
struct FLogicalExpression;
struct FMemberExpression;
struct FNewExpression;
struct FObjectExpression;
struct FSequenceExpression;
struct FParenthesizedExpression;
struct FThisExpression;
struct FUnaryExpression;
struct FUpdateExpression;
struct FArrowFunctionExpression;
struct FClassExpression;
struct FImportExpression;
struct FMetaProperty;
struct FSuper;
struct FTaggedTemplateExpression;
struct FTemplateLiteral;
struct FYieldExpression;
struct FAwaitExpression;
struct FImport;
struct FBigIntLiteral;
struct FOptionalMemberExpression;
struct FOptionalCallExpression;
struct FTypeCastExpression;
struct FJSXElement;
struct FJSXFragment;
struct FBindExpression;
struct FDoExpression;
struct FModuleExpression;
struct FTopicReference;
struct FTsInstantiationExpression;
struct FTsAsExpression;
struct FTsSatisfiesExpression;
struct FTsTypeAssertion;
struct FTsTypeCastExpression;
struct FTsNonNullExpression;
struct FEstreeChainExpression;
struct FEstreeLiteral;

/* Facilitates the type traits below, does not however implement anything */ 

struct FExpression : public FNodeBase { };

template<typename T>
constexpr bool IsExpression = std::is_base_of_v<FExpression, T>;

template<typename T>
concept Expression = requires(T a){ IsExpression<T>; };


struct FArrayExpression  : public FExpression
{
    std::vector<FExpression> Elements;
};

struct FDoExpression : public FNodeBase 
{
    bool bIsAsync; 
};

struct FObjectExpression : public FNodeBase 
{

};


/* --------------------------------------------------------------[ Expressions ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ Expressions ]-------------------------------------------------------------------- */




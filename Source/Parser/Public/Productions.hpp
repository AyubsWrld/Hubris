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

/* --------------------------------------------------------------[ @Enums ]------------------------------------------------------------------- */

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

/* --------------------------------------------------------------[ @Enums ]----------------------------------------------------------------------- */

/* --------------------------------------------------------------[ @Comments ]-------------------------------------------------------------------- */

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



/* --------------------------------------------------------------[ @Comments ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ @Nodebase ]-------------------------------------------------------------------- */

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

/* --------------------------------------------------------------[ @Nodebase ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ @Identifier ]-------------------------------------------------------------------- */ 

/* 
 *  An Identifier is an IdentifierName that is not a ReservedWord
 */

/* --------------------------------------------------------------[ @Identifier ]-------------------------------------------------------------------- */ 

/* --------------------------------------------------------------[ @Expressions ]-------------------------------------------------------------------- */

struct FAssignmentExpression;
struct FBinaryExpression;
struct FCallExpression;
struct FConditionalExpression;
struct FFunctionExpression;
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

struct FDoExpression : public FExpression
{
    bool bIsAsync; 
};

struct FObjectExpression : public FExpression
{

};

struct FIdentifier : public FNodeBase 
{
    std::string     Name; 
    bool            bIsOptional;
};

/* --------------------------------------------------------------[ @Expressions ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ @Directives ]-------------------------------------------------------------------- */
/*
 * A Directive is a special string literal that appears at the beginning
 * of a Program or BlockStatement body and alters how the code is interpreted.
 *
 * The most common example is:
 *      "use strict";
 *
 * Directives must appear before any non-directive statement in the body.
 * If placed elsewhere, they are treated as normal string literals.
 *
 * In the AST, directives are stored separately from regular statements
 * (e.g., Program::Directives, BlockStatement::Directives).
 */

//  This relation seems a bit superfluous when we can just have FDirective have a directive literal always?
struct FDirective : public FNodeBase { }; 

template<typename T>
constexpr bool IsDirective = std::is_base_of_v<FDirective, T>;

template<typename T>
concept Directive = requires(T a){ IsDirective<T>; };

struct FDirectiveLiteral : public FDirective 
{
    std::string Value;
};

/* --------------------------------------------------------------[ @Directives ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ @Statements ]-------------------------------------------------------------------- */

struct FStatement : public FNodeBase { }; 

template<typename T>
constexpr bool IsStatment = std::is_base_of_v<FStatement, T>;

template<typename T>
concept Statement = requires(T a){ IsStatment<T>; };

/* @under-constuction */
struct FBlockStatement : public FStatement
{
    std::vector<FStatement> Body;
    std::vector<FDirective> Label;
};

struct FBreakStatement : public FStatement
{
    std::optional<FIdentifier> Label;
};

struct FContinueStatement : public FStatement 
{

};

struct DebuggerStatement;
struct DoWhileStatement;
struct EmptyStatement;
struct ExpressionStatement;
struct ForInStatement;
struct ForStatement;
struct FunctionDeclaration;
struct IfStatement;
struct LabeledStatement;
struct ReturnStatement;
struct SwitchStatement;
struct ThrowStatement;
struct TryStatement;
struct VariableDeclaration;
struct WhileStatement;
struct WithStatement;
struct ClassDeclaration;
struct ExportAllDeclaration;
struct ExportDefaultDeclaration;
struct ExportNamedDeclaration;
struct ForOfStatement;
struct ImportDeclaration;
struct FlowDeclareClass;
struct FlowDeclareFunction;
struct FlowDeclareInterface;
struct FlowDeclareModule;
struct FlowDeclareModuleExports;
struct FlowDeclareTypeAlias;
struct FlowDeclareOpaqueType;
struct FlowDeclareVariable;
struct FlowDeclareExportDeclaration;
struct FlowEnumDeclaration;
struct FlowInterface;
struct FlowOpaqueType;
struct FlowTypeAlias;
struct TSDeclareFunction;
struct TsInterfaceDeclaration;
struct TsTypeAliasDeclaration;
struct TsEnumDeclaration;
struct TsModuleDeclaration;
struct TsImportEqualsDeclaration;
struct TsExportAssignment;
struct TsNamespaceExportDeclaration;

/* --------------------------------------------------------------[ @Statements ]-------------------------------------------------------------------- */






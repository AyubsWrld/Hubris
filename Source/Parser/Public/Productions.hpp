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

enum class RegExpFlag
{
    Global,        // g
    IgnoreCase,    // i
    Multiline,     // m
    Unicode,       // u
    DotAll,        // s
    Sticky,        // y
    UnicodeSets    // v
};

enum class EVariableDeclQualifier 
{
    Var,                        // "var"
    Let,                        // "let"
    Const,                      // "const"
    Using,                      // "using"
    Await_Using,                // "await using"
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
    NullishCoalescingAssign,    // ??=
    _MAX_
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

/* --------------------------------------------------------------[ @Literal ]-------------------------------------------------------------------- */

struct FLiteral : public FNodeBase { };

template<typename T>
constexpr bool IsLiteral = std::is_base_of_v<FLiteral, T>;

template<typename T>
concept Literal = requires(T a){ IsLiteral<T>; };

struct FRegExpLiteral : public FLiteral 
{ 
    std::string Pattern;
};

struct FNullLiteral : public FLiteral {  };

struct FStringLiteral : public FLiteral 
{ 
    std::string Value;
};

struct FBooleanLiteral : public FLiteral 
{ 
    bool bValue;
};

struct FNumericLiteral : public FLiteral 
{ 
    union 
    {
        double  FloatingPointValue;
        I64     IntegralValue;
    } Value;
};

// FIXME: using 2 64 bit integers to represent 2^128. 
// Right now it's more like a fixed-width 128-bit integer. see C _int128 perhaps utilize a method that allows the value to "grow" dynamically
// [limb]-[limb]-[limb]. 

struct FBigIntLiteral : public FLiteral 
{ 
    U64 High;   // Uppers 64bits
    U64 Low;    // Lower 64bits
};

/* --------------------------------------------------------------[ @Literal ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ @Identifier ]-------------------------------------------------------------------- */ 

/* 
 *  An Identifier is an IdentifierName that is not a ReservedWord
*/

struct FIdentifier : public FNodeBase 
{
    std::string     Name; 
    bool            bIsOptional;
};

//TODO: not in spec.
struct FTypeAnnotationBase : public FNodeBase
{

};

/* --------------------------------------------------------------[ @Identifier ]-------------------------------------------------------------------- */ 

/* --------------------------------------------------------------[ @Pattern ]-------------------------------------------------------------------- */

// NOTE: Unfaithful in that it doesn't concern itself with deriving from "FHasDecorator".
struct FPatternBase : public FNodeBase 
{
    bool bIsOptional;
    std::optional<FTypeAnnotationBase> TypeAnnotation;
};

template<typename T>
constexpr bool IsPattern  = std::is_base_of_v<FPatternBase, T>;

template<typename T> 
concept Pattern = requires(T a) { IsPattern<T>; };

// struct FIdentifier : public FPatternBase { }; // Problem with redecl

// represents object destructuring pattern:
// e.g. : const { a, b } = obj;
struct FObjectPattern : public FPatternBase { };


// represents array destructuring pattern:
// e.g. : const [a, b] = arr;
struct FArrayPattern : public FPatternBase { };


// represents a rest element inside a pattern:
// e.g. : const [a, ...rest] = arr;
struct FRestElement : public FPatternBase { };


// Represents a default value assignment inside a pattern:
// e.g. : function f(x = 10) {}
struct FAssignmentPattern : public FPatternBase { };


// represents a void pattern.
// corresponds to "void" usage as a pattern placeholder.
struct FVoidPattern : public FPatternBase { };


/* --------------------------------------------------------------[ @Pattern ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ @Assignable ]-------------------------------------------------------------------- */

/* 
 * An Assignable represents an LValue — something that can appear
 * on the left-hand side of an assignment.
*/

struct FAssignable : public FNodeBase { };

template<typename T>
constexpr bool IsAssignable = std::is_base_of_v<FAssignable, T>;

template<typename T>
concept Assignable = requires(T a){ IsLiteral<T>; };

// represents property access that can be assigned to:
// e.g. : obj.value = 42;
struct FMemberExpression : public FAssignable { };


// represents a parenthesized expression that still resolves to an assignable:
// e.g: (x) = 5;
struct FParenthesizedExpression : public FAssignable { };


// represents a TypeScript-style type cast that still resolves to an assignable:
// e.g.: (x as number) = 10;
struct FTsTypeCastExpression : public FAssignable { };


// represents a standard type cast expression that resolves to an assignable:
// example: (<number>x) = 10;
struct FTypeCastExpression : public FAssignable { };

/* --------------------------------------------------------------[ @Assignable ]-------------------------------------------------------------------- */



/* --------------------------------------------------------------[ @Expressions ]-------------------------------------------------------------------- */


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

/* --------------------------------------------------------------[ @Expressions ]-------------------------------------------------------------------- */

/* --------------------------------------------------------------[ @Decorators ]-------------------------------------------------------------------- */
/*
 * metadata annotations that can appear
 * before classes, methods, properties, or parameters.
 *   @sealed
 *   class MyClass {}
 *
 *   @log
 *   method() {}
*/

// represents a single decorator.
// It wraps an expression that will be evaluated as the decorator.
struct FDecorator : public FNodeBase 
{    
    
    FExpression Expression; // @log → "log" is stored as an expression.
};

// base struct for any node that can have decorators attached.
struct FHasDecorator : public FNodeBase 
{    
    // it is optional because most nodes will not have decorators.
    std::optional<std::vector<FDecorator>> Decorators;
};

/* --------------------------------------------------------------[ @Decorators ]-------------------------------------------------------------------- */

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
    std::vector<FStatement> Body;   // { stmt; stmt; }
    std::vector<FDirective> Label;  // "use strict"
};

struct FBreakStatement : public FStatement
{
    std::optional<FIdentifier> Label; // break; / break label;
};

struct FContinueStatement : public FStatement 
{
    std::optional<FIdentifier> Label; // continue; / continue label;
};

struct FDebuggerStatement : public FStatement { }; // debugger;

struct FDoWhileStatement : public FStatement 
{
    FStatement  Body; // do { ... }
    FExpression Test; // while (x > 0)
};

struct FEmptyStatement : public FStatement { }; // ;

struct FExpressionStatement : public FStatement 
{
    FExpression                 Expression; // foo()
    std::optional<FDirective>   Directive;  // "use strict"
};

struct FForInStatement : public FStatement 
{
    bool bIsAsync; // for (x in obj) / for await (x in obj)
};

struct FVariableDeclaration : public FStatement 
{
    FIdentifier             Identifier; // x
    EVariableDeclQualifier  Kind;       // var / let / const / using / await using
};

struct FForStatement : public FStatement 
{
    // for (let i = 0; i < n; i++) { ... }
    union UInit
    {
        FExpression             Expression; // i = 0
        FVariableDeclaration    Decl;       // let i = 0
    };
    std::optional<UInit>    Init;   // let i = 0
    FExpression             Test;   // i < n
    FExpression             Update; // i++
    FStatement              Body;   // { ... }
};

struct FFunctionDeclaration : public FStatement 
{
    FIdentifier Identifier; // function foo() { ... }
};

struct FIfStatement : public FStatement 
{
    // if (x > 0) { ... } else { ... }
    FExpression                 Test;       // x > 0
    FStatement                  Consequent; // { ... }
    std::optional<FStatement>   Alternate;  // else { ... }
};

struct FLabeledStatement : public FStatement 
{
    FIdentifier Label; // outer:
    FStatement  Body;  // while (...) { break outer; }
};

struct FReturnStatement : public FStatement
{
    FExpression Argument; // return x
};

struct FSwitchCase : public FNodeBase 
{
    // case 1: ... / default: ...
    std::optional<FExpression>  Test;       // 1  (nullopt = default)
    std::vector<FStatement>     Consequent; // stmt; ...
};

struct FSwitchStatement : public FStatement 
{
    // switch (x) { case 1: ... }
    FExpression                 Discriminant; // x
    std::vector<FSwitchCase>    Cases;
};

struct FThrowStatement : public FStatement 
{
    FExpression Argument; // throw new Error()
};

struct FTryStatement : public FStatement 
{
    FBlockStatement Block;     // try { ... }
    FBlockStatement Finalizer; // finally { ... }
};

struct FWhileStatement : public FStatement 
{
    // while (x > 0) { ... }
    FExpression Test; // x > 0
    FStatement  Body; // { ... }
};

struct FWithStatement : public FStatement 
{
    // with (obj) { ... }
    FExpression Object; // obj
    FStatement  Body;   // { ... }
};

struct FClassDeclaration : public FStatement 
{
    FIdentifier Identifier; // class Foo { ... }
};

struct FExportAllDeclaration : public FStatement 
{

};

struct FForOfStatement : public FStatement 
{
    bool bIsAsync; // for (x of iter) / for await (x of iter)
};


// More complex types.
struct FTSDeclareFunction;
struct FTsInterfaceDeclaration;
struct FTsTypeAliasDeclaration;
struct FTsEnumDeclaration;
struct FTsModuleDeclaration;
struct FTsImportEqualsDeclaration;
struct FTsExportAssignment;
struct FTsNamespaceExportDeclaration;
struct FExportDefaultDeclaration;
struct FExportNamedDeclaration;
struct FImportDeclaration;
struct FFlowDeclareClass;
struct FFlowDeclareFunction;
struct FFlowDeclareInterface;
struct FFlowDeclareModule;
struct FFlowDeclareModuleExports;
struct FFlowDeclareTypeAlias;
struct FFlowDeclareOpaqueType;
struct FFlowDeclareVariable;
struct FFlowDeclareExportDeclaration;
struct FFlowEnumDeclaration;
struct FFlowInterface;
struct FFlowOpaqueType;
struct FFlowTypeAlias;

/* --------------------------------------------------------------[ @Statements ]-------------------------------------------------------------------- */






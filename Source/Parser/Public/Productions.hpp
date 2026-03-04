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

enum class EVariableDeclQualifier 
{
    Var,                        // "var"
    Let,                        // "var"
    Const,                      // "var"
    Using,                      // "var"
    Await_Using,                // "var"
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
    std::optional<FIdentifier> Label;
};

struct FDebuggerStatement : public FStatement {  };

struct FDoWhileStatement : public FStatement 
{
    FStatement  Body;   // { ... } 
    FExpression Test;   // (expr) condition.
};

struct FEmptyStatement : public FStatement {  };

struct FExpressionStatement : public FStatement 
{
    FExpression Expression; 
    std::optional<FDirective> Directive;  // for estree
};

struct FForInStatement : public FStatement 
{
    //FIXME: "Shouldn't be here, but have to declare it because it's assigned to a ForInOf unconditionally."
    bool bIsAsync;
};

struct FVariableDeclaration : public FStatement 
{
    FIdentifier             Identifier; // Identifier name;
    EVariableDeclQualifier  Kind;       // Qualifier: ("var" || "let" || "const" || "using" || "await using");
};

struct FForStatement : public FStatement 
{
    // for (expr; expr; expr) stmt
    union UInit
    {
        FExpression             Expression;
        FVariableDeclaration    Decl;
    };

    std::optional<UInit>    Init; // Init statement (expr; expr; expr)
    FExpression             Test; // (expr) condition.
    FExpression             Update;
    FStatement              Body; // { ... }
};


struct FFunctionDeclaration : public FStatement 
{
    FIdentifier Identifier;
};

struct FIfStatement : public FStatement 
{
    // if (expr) stmt; else stmt (optional)
    FExpression                     Test;       // (expr)
    FStatement                      Consequent; // stmt
    std::optional<FStatement>       Alternate; // stmt
};

struct FLabeledStatement : public FStatement 
{
    FIdentifier     Label; 
    FStatement      Body;
};

struct FReturnStatement : public FStatement
{
    FExpression Argument; 
};

struct FSwitchCase : public FNodeBase 
{ 
    // ( Test ) stmt...
    std::optional<FExpression>  Test;
    std::vector<FStatement>     Consequent;
};

struct SwitchStatement : public FStatement 
{
    // switch (discriminant) { ... cases ... }
    FExpression Discriminant; 
    std::vector<FSwitchCase> Cases;
};

struct ThrowStatement;
struct TryStatement;
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






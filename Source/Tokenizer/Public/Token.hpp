#pragma once 
#include "ShorthandTypes.hpp"
#include "Enumerators.hpp"
#include <optional>
#include <utility>

struct FTokenAttributes
{
    std::optional<std::string>         Keyword;
    std::optional<U64>  BinaryOperation;
    struct 
    {
        unsigned char   BeforeExpr : 1;
        unsigned char   StartsExpr : 1;
        unsigned char   RightAssociative : 1;
        unsigned char   IsLoop : 1;
        unsigned char   Prefix : 1;
        unsigned char   Postfix : 1;
        unsigned char   Pad : 2;
    } Flags;
};

enum class ETokenType
{
    BracketLeft,            // [
    BracketRight,           // ]
    BraceLeft,              // {
    BraceBarLeft,           // {|
    BraceRight,             // }
    BraceBarRight,          // |}
    ParenthesisLeft,        // (
    ParenthesisRight,       // )

    Comma,                  // ,
    Semicolon,              // ;
    Colon,                  // :
    DoubleColon,            // ::
    Dot,                    // .

    Question,               // ?
    QuestionDot,            // ?.
    Arrow,                  // =>

    Template,               // template
    Ellipsis,               // ...

    BackQuote,              // `
    DollarBraceLeft,        // ${
    TemplateTail,           // ...`
    TemplateNonTail,        // ...${

    At,                     // @
    Hash,                   // #
    InterpreterDirective,   // #!...

    // Assignment operators
    Eq,                     // =
    Assign,                 // _=
    SlashAssign,            // _=
    XorAssign,              // _=
    ModuloAssign,           // _=

    // Unary / update operators
    IncDec,                 // ++ / --
    Bang,                   // !
    Tilde,                  // ~

    // Hack topic tokens
    DoubleCaret,            // ^^
    DoubleAt,               // @@

    // Binary operators
    Pipeline,               // |>
    NullishCoalescing,      // ??
    LogicalOR,              // ||
    LogicalAND,             // &&
    BitwiseOR,              // |
    BitwiseXOR,             // ^
    BitwiseAND,             // &
    Equality,               // == / != / === / !==
    LessThan,               // <
    GreaterThan,            // >
    Relational,             // < > <= >=
    BitShift,               // << >> >>>
    BitShiftLeft,           // <<
    BitShiftRight,          // >> >>>
    PlusMinus,              // + / -
    Modulo,                 // %
    Star,                   // *
    Slash,                  // /
    Exponent,               // **

    // Keywords
    In,                   // in
    Instanceof,           // instanceof
    Break,                // break
    Case,                 // case
    Catch,                // catch
    Continue,             // continue
    Debugger,             // debugger
    Default,              // default
    Else,                 // else
    Finally,              // finally
    Function,             // function
    If,                   // if
    Return,               // return
    Switch,               // switch
    Throw,                // throw
    Try,                  // try
    Var,                  // var
    Const,                // const
    With,                 // with
    New,                  // new
    This,                 // this
    Super,                // super
    Class,                // class
    Extends,              // extends
    Export,               // export
    Import,               // import
    Null,                 // null
    True,                 // true
    False,                // false
    Typeof,               // typeof
    Void,                 // void
    Delete,               // delete
    Do,                   // do
    For,                  // for
    While,                // while

    // Keyword-like identifiers
    As,                   // as
    Assert,               // assert
    Async,                // async
    Await,                // await
    Defer,                // defer
    From,                 // from
    Get,                  // get
    Let,                  // let
    Meta,                 // meta
    Of,                   // of
    Sent,                 // sent
    Set,                  // set
    Source,               // source
    Static,               // static
    Using,                // using
    Yield,                // yield

    // Flow / TS keyword-like
    Asserts,              // asserts
    Checks,               // checks
    Exports,              // exports
    Global,               // global
    Implements,           // implements
    Intrinsic,            // intrinsic
    Infer,                // infer
    Is,                   // is
    Mixins,               // mixins
    Proto,                // proto
    Require,              // require
    Satisfies,            // satisfies
    Keyof,                // keyof
    Readonly,             // readonly
    Unique,               // unique
    Abstract,             // abstract
    Declare,              // declare
    Enum,                 // enum
    Module,               // module
    Namespace,            // namespace
    Interface,            // interface
    Type,                 // type
    Opaque,               // opaque

    Name,                   // name
    Placeholder,            // %%
    String,                 // string
    Number,                 // num
    BigInt,                 // bigint
    RegExp,                 // regexp
    PrivateName,            // #name

    EndOfFile,              // eof

    // JSX
    JSXName,                // jsxName
    JSXText,                // jsxText
    JSXTagStart,            // jsxTagStart
    JSXTagEnd,              // jsxTagEnd

    _MAX_
};

// Maps tokens to their attributes. 
constexpr FTokenAttributes kTokenAttributeMap[std::to_underlying(ETokenType::_MAX_)] = {

};


// The `ExportedTokenType` is exported via `tokTypes` and accessible
// when `tokens: true` is enabled. Unlike internal token type, it provides
// metadata of the tokens.

struct FToken 
{
    constexpr bool IsIdentifier() noexcept;
    constexpr bool KeywordOrIdentifierIsKeyword() noexcept;
    constexpr bool IsLiteralPropertyName() noexcept;
    constexpr bool PrefixesExpression() noexcept;
    constexpr bool CanStartExpression() noexcept;
    constexpr bool IsAssignment() noexcept;
    constexpr bool IsFlowInterfaceOrTypeOrOpaque() noexcept;
    constexpr bool IsLoop() noexcept;
    constexpr bool IsOperator() noexcept;
    constexpr bool IsPostfix() noexcept;
    constexpr bool IsPrefix() noexcept;
    constexpr bool IsTSTypeOperator() noexcept;
    constexpr bool IsTSDeclarationStart() noexcept;
    constexpr bool IsRightAssociative() noexcept;

    // Comparison operators 
    
    constexpr bool operator==(const FToken& other) { return false; } 
};





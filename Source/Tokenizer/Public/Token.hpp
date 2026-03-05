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
    /*
    @purpose:            Determines whether the current token represents a valid
                            JavaScript/TypeScript identifier. Identifiers include user-
                            defined names such as variables, functions, classes, and
                            other symbol references used within expressions or declarations.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token type corresponds to an
                                            identifier or identifier-like token.
    
    @notes:              Used by the parser when resolving names in expressions,
                            bindings, and declarations.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsIdentifier() noexcept;
    
    /*
    @purpose:            Determines whether the current token is either an identifier
                            or a keyword that behaves as a reserved word in the grammar.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a keyword token.
    
    @notes:              Used during parsing to distinguish reserved language
                            constructs from user-defined identifiers.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool KeywordOrIdentifierIsKeyword() noexcept;
    
    /*
    @purpose:            Determines whether the current token may legally appear
                            as a literal property name within an object literal or
                            class property definition.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token may be used as a property name.
    
    @notes:              Includes identifiers, string literals, numeric literals,
                            and certain keyword-like tokens depending on language rules.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsLiteralPropertyName() noexcept;
    
    /*
    @purpose:            Determines whether the current token acts as a prefix
                            operator that begins an expression.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token prefixes an expression.
    
    @notes:              Includes operators such as '!', '~', 'typeof', 'void',
                            'delete', and similar unary prefix operators.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool PrefixesExpression() noexcept;
    
    /*
    @purpose:            Determines whether the current token type may legally
                            begin a JavaScript/TypeScript expression.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token can appear at the start
                                            of an expression.
    
    @notes:              Used by expression parsers to decide when expression
                            parsing may begin.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool CanStartExpression() noexcept;
    
    /*
    @purpose:            Determines whether the current token represents an
                            assignment operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token corresponds to an
                                            assignment operator.
    
    @notes:              Includes '=', '+=', '-=', '*=', '/=', and other
                            assignment variants depending on tokenizer support.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsAssignment() noexcept;
    
    /*
    @purpose:            Determines whether the current token corresponds to
                            Flow/TypeScript interface, type, or opaque declarations.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token begins or represents
                                            a Flow/TypeScript interface/type/opaque construct.
    
    @notes:              Used in Flow and TypeScript plugin parsing modes.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsFlowInterfaceOrTypeOrOpaque() noexcept;
    
    /*
    @purpose:            Determines whether the token represents a looping
                            control-flow keyword.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token corresponds to a loop keyword.
    
    @notes:              Includes 'for', 'while', and 'do'.
                            Used to detect loop constructs during statement parsing.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsLoop() noexcept;
    
    /*
    @purpose:            Determines whether the current token is classified
                            as an operator in the grammar.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token functions as an operator.
    
    @notes:              Includes binary, prefix, postfix, and assignment operators.
                            Used for expression precedence and parsing logic.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsOperator() noexcept;
    
    /*
    @purpose:            Determines whether the current token represents a
                            postfix unary operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a postfix operator.
    
    @notes:              Includes tokens such as '++' and '--' when used after
                            an expression.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsPostfix() noexcept;
    
    /*
    @purpose:            Determines whether the current token represents a
                            prefix unary operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a prefix operator.
    
    @notes:              Includes operators such as '!', '~', 'typeof', 'void',
                            and 'delete'.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsPrefix() noexcept;
    
    /*
    @purpose:            Determines whether the token represents a TypeScript
                            type operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a TypeScript
                                            type operator.
    
    @notes:              Includes operators such as 'keyof', 'readonly',
                            and 'unique'.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsTSTypeOperator() noexcept;
    
    /*
    @purpose:            Determines whether the token may begin a TypeScript
                            declaration construct.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token starts a TypeScript
                                            declaration.
    
    @notes:              Includes tokens such as 'abstract', 'declare',
                            'enum', 'module', 'namespace', 'interface', and 'type'.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsTSDeclarationStart() noexcept;
    
    /*
    @purpose:            Determines whether the operator represented by the
                            current token is right-associative.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the operator is right-associative.
    
    @notes:              Used for operators such as exponentiation '**'
                            where evaluation order differs from standard
                            left-associative binary operators.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsRightAssociative() noexcept;
    
    /*
    @purpose:            Compares this token instance with another token
                            to determine equality.
    
    @param:              [in]            const FToken& other
                                            Token instance to compare against.
    
                                        return
    
    @code:               bool            True if both tokens represent the same
                                            token type and value.
    
    @notes:              Comparison criteria typically include token type
                            and any associated token value.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool operator==(const FToken& other);

};





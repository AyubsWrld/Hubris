/*
   ================================================================================================================
                                                    FILE OVERVIEW
   ================================================================================================================

   @file:               Token.hpp

   @purpose:            Defines the token representation used by the JavaScript / TypeScript lexer and parser.
                        This file provides the fundamental structures, enumerations, and helper functions used
                        to classify and reason about tokens produced during the scanning process.

                        Tokens represent the smallest meaningful units of source code such as identifiers,
                        literals, operators, punctuation, and keywords. These tokens are emitted by the
                        tokenizer and consumed by the parser to construct the Abstract Syntax Tree (AST).

                        The types and utilities defined here enable fast classification of tokens during
                        parsing and provide a compact representation suitable for high-performance language
                        tooling.

   @token-design:

        The assignment of fine-grained, information-carrying token type objects allows the
        tokenizer to store contextual information about tokens in a form that is extremely
        cheap for the parser to query during parsing.

        Instead of repeatedly performing expensive conditional logic during parsing, token
        types encode structural properties of the token directly. The parser can therefore
        inspect token behavior through simple flag checks.

        All token type variables begin with an underscore in the original tokenizer design
        to make them easily distinguishable from other identifiers.

        Several structural flags are associated with tokens:

            beforeExpr
                Indicates that a token may legally appear before an expression.
                This property is used to disambiguate grammar constructs such as:

                    • Binary expressions ( < )
                    • JSX tag starts ( <Tag> )
                    • Object literals vs JSX text contexts

                This property is typically updated through tokenizer context
                transitions.

            startsExpr
                Indicates that a token may begin a valid expression or subexpression.
                This is used to determine whether a token can serve as the argument
                of constructs such as `yield`, unary operators, or other expression
                contexts.

            isLoop
                Marks keywords that introduce looping constructs such as:

                    • for
                    • while
                    • do

                This information is required when parsing labeled statements so the
                parser can determine whether a `continue` statement may legally
                target a particular label.

   @design:             Token classification is implemented using lightweight constexpr
                        helper functions so that many checks may be evaluated at compile
                        time or optimized away by the compiler.

                        The token system is designed to mirror the behavior of modern
                        JavaScript parsers such as Babel, Acorn, and V8 while maintaining
                        a strongly typed C++ representation.

   @usage:              Tokens are produced by the tokenizer during lexical scanning of
                        source code. The parser consumes these tokens sequentially to
                        construct syntactic structures and eventually generate the AST.

                        Helper predicates defined in this file are used extensively by
                        the parser to determine grammar behavior based on token type.

   @notes:              This file does not perform lexical analysis itself. It only defines
                        token types and utilities used by the tokenizer and parser.

                        All token classification logic must remain consistent with the
                        grammar rules implemented in the parser.

   ================================================================================================================
*/

#pragma once 
#include "ShorthandTypes.hpp"
#include "Enumerators.hpp"
#include <optional>
#include <type_traits>
#include <utility>



/*
 *  Enumeration describing every token recognized by the lexer including punctuation,
 *  operators, keywords, literals, JSX tokens, and TypeScript/Flow extensions.
*/
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

// TODO: Bitmasks for easy validation. 
enum
{
    BEFORE_EXPR         =   (1u << 1),
    STARTS_EXPR         =   (1u << 2),
    RIGHT_ASSOCIATIVE   =   (1u << 3),
    IS_LOOP             =   (1u << 4),
    PREFIX              =   (1u << 5),
    POSTFIX             =   (1u << 6)
};

struct FTokenFlags
{
    U8      BeforeExpr :        1   =   false;          // whether token can legally appear before an expression.
    U8      StartsExpr :        1   =   false;          // whether token can legally start an expression ( "throw", "return").
    U8      RightAssociative :  1   =   false;          // tokens associativity, defaults to left associative (false) unless otherwise specified. 
    U8      IsLoop :            1   =   false;          // whether the token implies source jumping 
    U8      IsAssign:           1   =   false;          // whether the token can be used within an assignment statement.
    U8      Prefix :            1   =   false;          // fixity of token. note that we the flags must include both postfix and prefix for operators that can act as both ('--/++')
    U8      Postfix :           1   =   false;          // fixity of token. note that we the flags must include both postfix and prefix for operators that can act as both ('--/++')
    U8      : 1;                                        // padding bit.
};



struct FToken 
{
    
    FTokenFlags                 Flags;
    std::optional<U8>           BinOp;          // Encodes Precedence.
    ETokenType                  TokenType;      // Token Type for tagging attributes to the token it represents.

    /*
    @purpose:               Determines whether the current token represents a valid
                            JavaScript/TypeScript identifier. Identifiers include user-
                            defined names such as variables, functions, classes, and
                            other symbol references used within expressions or declarations.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token type corresponds to an
                                            identifier or identifier-like token.
    
    @notes:                 Used by the parser when resolving names in expressions,
                            bindings, and declarations.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsIdentifier() const noexcept
    {
        return TokenType >= ETokenType::As && TokenType >= ETokenType::Placeholder;
    }
    
    /*
    @purpose:               Determines whether the current token is either an identifier
                            or a keyword that behaves as a reserved word in the grammar.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a keyword token.
    
    @notes:                 Used during parsing to distinguish reserved language
                            constructs from user-defined identifiers.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool KeywordOrIdentifierIsKeyword() const noexcept
    {
        return TokenType <= ETokenType::While;
    }
    
    /*
    @purpose:               Determines whether the current token is either an identifier
                            or a keyword that behaves as a reserved word in the grammar.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a keyword token.
    
    @notes:                 Used during parsing to distinguish reserved language
                            constructs from user-defined identifiers.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsKeywordOrIdentifier() const noexcept
    {
        return TokenType >= ETokenType::In && TokenType <= ETokenType::Placeholder;
    }

    /*
    @purpose:               Determines whether the current token may legally appear
                            as a literal property name within an object literal or
                            class property definition.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token may be used as a property name.
    
    @notes:                 Includes identifiers, string literals, numeric literals,
                            and certain keyword-like tokens depending on language rules.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsLiteralPropertyName() const noexcept
    {
        return TokenType >= ETokenType::In && TokenType <= ETokenType::BigInt;
    }
    
    /*
    @purpose:               Determines whether the current token acts as a prefix
                            operator that begins an expression.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token prefixes an expression.
    
    @notes:                 Includes operators such as '!', '~', 'typeof', 'void',
                            'delete', and similar unary prefix operators.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool PrefixesExpression() const noexcept
    {
        return Flags.BeforeExpr;
    }
    
    /*
    @purpose:               Determines whether the current token type may legally
                            begin a JavaScript/TypeScript expression.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token can appear at the start
                                            of an expression.
    
    @notes:                 Used by expression parsers to decide when expression
                            parsing may begin.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool CanStartExpression() const noexcept
    {
        return Flags.StartsExpr;
    }
    
    /*
    @purpose:               Determines whether the current token represents an
                            assignment operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token corresponds to an
                                            assignment operator.
    
    @notes:                 Includes '=', '+=', '-=', '*=', '/=', and other
                            assignment variants depending on tokenizer support.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsAssignment() const noexcept
    {
        return TokenType >= ETokenType::Eq && TokenType <= ETokenType::ModuloAssign;
    }
    
    /*
    @purpose:               Determines whether the current token corresponds to
                            Flow/TypeScript interface, type, or opaque declarations.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token begins or represents
                                            a Flow/TypeScript interface/type/opaque construct.
    
    @notes:                 Used in Flow and TypeScript plugin parsing modes.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsFlowInterfaceOrTypeOrOpaque() const noexcept
    {
        return TokenType >= ETokenType::Interface && TokenType <= ETokenType::Opaque;
    }
    
    /*
    @purpose:               Determines whether the token represents a looping
                            control-flow keyword.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token corresponds to a loop keyword.
    
    @notes:                 Includes 'for', 'while', and 'do'.
                            Used to detect loop constructs during statement parsing.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsLoop() const noexcept
    {
        return TokenType >= ETokenType::Do && TokenType <= ETokenType::While;
    }

    /*
    @purpose:               Determines whether the token represents a looping
                            control-flow keyword.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token corresponds to a loop keyword.
    
    @notes:                 Includes 'for', 'while', and 'do'.
                            Used to detect loop constructs during statement parsing.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsKeyword() const noexcept
    {
        return TokenType >= ETokenType::In && TokenType <= ETokenType::While;
    }
    
    /*
    @purpose:               Determines whether the current token is classified
                            as an operator in the grammar.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token functions as an operator.
    
    @notes:                 Includes binary, prefix, postfix, and assignment operators.
                            Used for expression precedence and parsing logic.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsOperator() const noexcept
    {
        return TokenType >= ETokenType::Pipeline && TokenType <= ETokenType::Instanceof;
    }
    
    /*
    @purpose:               Determines whether the current token represents a
                            postfix unary operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a postfix operator.
    
    @notes:                 Includes tokens such as '++' and '--' when used after
                            an expression.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsPostfix() const noexcept
    {
        return Flags.Postfix;
    }
    
    /*
    @purpose:               Determines whether the current token represents a
                            prefix unary operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a prefix operator.
    
    @notes:                 Includes operators such as '!', '~', 'typeof', 'void',
                            and 'delete'.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsPrefix() const noexcept
    {
        return Flags.Prefix;
    }
    
    /*
    @purpose:               Determines whether the token represents a TypeScript
                            type operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token is a TypeScript
                                            type operator.
    
    @notes:                 Includes operators such as 'keyof', 'readonly',
                            and 'unique'.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsTSTypeOperator() const noexcept
    {
        return TokenType >= ETokenType::Keyof && TokenType <= ETokenType::Unique;
    }
    
    /*
    @purpose:               Determines whether the token may begin a TypeScript
                            declaration construct.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the token starts a TypeScript
                                            declaration.
    
    @notes:                 Includes tokens such as 'abstract', 'declare',
                            'enum', 'module', 'namespace', 'interface', and 'type'.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsTSDeclarationStart() const noexcept
    {
        return TokenType >= ETokenType::Abstract && TokenType <= ETokenType::Type;
    }
    
    /*
    @purpose:               Determines whether the operator represented by the
                            current token is right-associative.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the operator is right-associative.
    
    @notes:                 Used for operators such as exponentiation '**'
                            where evaluation order differs from standard
                            left-associative binary operators.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsRightAssociative() const noexcept
    {
        return Flags.RightAssociative;
    }
    
    /*
    @purpose:               Determines whether the operator represented by the
                            current token is a binary operator.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the operator is a binary operator.
    
    */
    constexpr bool IsBinaryOperator() const noexcept
    {
        return BinOp.has_value();
    }

    /*
    @purpose:               Given a binary opeartor return operator precedence 
                            of token.
    
    @param:              none
    
                                        return
    
    @code:               std::optional<U8> Number encoding tokens operator precedence if binary operator, std::nullopt_t otherwise.
    
    @notes:                 Operator precedence is encoded within a 
                            tokens BinOp field. If defined it returns
                            a number which can be used to compare tokens 
                            representing binary operators based on their 
                            operator precedence. It is the callers job 
                            to retrieve the value from the optional.
    */
    constexpr std::optional<U8> OperatorPrecedence() const noexcept
    {
        return BinOp;
    }

    /*
    @purpose:               Determines whether the operator represented by the
                            current token is right-associative.
    
    @param:              none
    
                                        return
    
    @code:               bool            True if the operator is right-associative.
    
    @notes:                 Used for operators such as exponentiation '**'
                            where evaluation order differs from standard
                            left-associative binary operators.
                            noexcept guarantee — does not throw exceptions.
    */
    constexpr bool IsTemplate() const noexcept;

    /*
    @purpose:               Compares this token instance with another token
                            to determine equality.
    
    @param:              [in]            const FToken& other
                                            Token instance to compare against.
    
                                        return
    
    @code:               bool            True if both tokens represent the same
                                            token type and value.
    
    @notes:                 Comparison criteria typically include token type
                            and any associated token value.
                            noexcept guarantee — does not throw exceptions.
    */
    //constexpr bool operator==(const FToken& other) const;

};

/*
@purpose:               Given a token type, return the tokens attributes.

@param:              [in]           ETokenType InType

                                    return

@code:               const FToken&  Tokens attributes. 

*/

const FToken& GetTokenAttributes(ETokenType InToken);


// Maps tokens to their attributes. 

static inline constexpr FToken kTokenAttributes[std::to_underlying(ETokenType::_MAX_)] =
{
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true }, .TokenType = ETokenType::BracketLeft },           // [
    FToken{ .Flags = { }, .TokenType = ETokenType::BracketRight },                                                  // ]
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true }, .TokenType = ETokenType::BraceLeft },             // {
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true }, .TokenType = ETokenType::BraceBarLeft },          // {|
    FToken{ .Flags = { }, .TokenType = ETokenType::BraceRight },                                                    // }
    FToken{ .Flags = { }, .TokenType = ETokenType::BraceBarRight },                                                 // |}
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true }, .TokenType = ETokenType::ParenthesisLeft },       // (
    FToken{ .Flags = { }, .TokenType = ETokenType::ParenthesisRight },                                              // )
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Comma },                                      // ,
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Semicolon },                                  // ;
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Colon },                                      // :
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::DoubleColon },                                // ::
    FToken{ .Flags = { }, .TokenType = ETokenType::Dot },                                                           // .
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Question },                                   // ?
    FToken{ .Flags = { }, .TokenType = ETokenType::QuestionDot },                                                   // ?.
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Arrow },                                      // =>
    FToken{ .Flags = { }, .TokenType = ETokenType::Template },                                                      // template
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Ellipsis },                                   // ...
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::BackQuote },                                  // `
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true }, .TokenType = ETokenType::DollarBraceLeft },       // ${
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::TemplateTail },                               // ...`
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true }, .TokenType = ETokenType::TemplateNonTail },       // ...${
    FToken{ .Flags = { }, .TokenType = ETokenType::At },                                                            // @
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Hash },                                       // #
    FToken{ .Flags = { }, .TokenType = ETokenType::InterpreterDirective },                                          // #!...

    // Assignment operators
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true }, .TokenType = ETokenType::Eq },                      // =
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true }, .TokenType = ETokenType::Assign },                  // _=
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true }, .TokenType = ETokenType::SlashAssign },             // _=
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true }, .TokenType = ETokenType::XorAssign },               // _=
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true }, .TokenType = ETokenType::ModuloAssign },            // _=

    // Unary / update operators
    FToken{ .Flags = { .StartsExpr = true, .Prefix = true, .Postfix = true }, .TokenType = ETokenType::IncDec },                  // ++/--
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true }, .TokenType = ETokenType::Bang },                 // !
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true }, .TokenType = ETokenType::Tilde },                // ~

    // Hack topic tokens
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::DoubleCaret },                                // ^^
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::DoubleAt },                                   // @@

    // Binary operators
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 0, .TokenType = ETokenType::Pipeline },                      // |>
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 1, .TokenType = ETokenType::NullishCoalescing },             // ??
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 1, .TokenType = ETokenType::LogicalOR },                     // ||
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 2, .TokenType = ETokenType::LogicalAND },                    // &&
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 3, .TokenType = ETokenType::BitwiseOR },                     // |
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 4, .TokenType = ETokenType::BitwiseXOR },                    // ^
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 5, .TokenType = ETokenType::BitwiseAND },                    // &
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 6, .TokenType = ETokenType::Equality },                      // ==/!=
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 7, .TokenType = ETokenType::LessThan },                      // 
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 7, .TokenType = ETokenType::GreaterThan },                   // >
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 7, .TokenType = ETokenType::Relational },                    // </>/<=/>=
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 8, .TokenType = ETokenType::BitShift },                      // <</>>/>>>
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 8, .TokenType = ETokenType::BitShiftLeft },                  // 
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 8, .TokenType = ETokenType::BitShiftRight },                 // >>/>>>
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true }, .BinOp = 9, .TokenType = ETokenType::PlusMinus },  // +/-
    FToken{ .Flags = { .StartsExpr = true }, .BinOp = 10, .TokenType = ETokenType::Modulo },                       // %
    FToken{ .Flags = { }, .BinOp = 10, .TokenType = ETokenType::Star },                                             // *
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 10, .TokenType = ETokenType::Slash },                        // /
    FToken{ .Flags = { .BeforeExpr = true, .RightAssociative = true }, .BinOp = 11, .TokenType = ETokenType::Exponent }, // **

    // Keywords
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 7, .TokenType = ETokenType::In },                            // in
    FToken{ .Flags = { .BeforeExpr = true }, .BinOp = 7, .TokenType = ETokenType::Instanceof },                    // instanceof
    FToken{ .Flags = { }, .TokenType = ETokenType::Break },                                                         // break
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Case },                                       // case
    FToken{ .Flags = { }, .TokenType = ETokenType::Catch },                                                         // catch
    FToken{ .Flags = { }, .TokenType = ETokenType::Continue },                                                      // continue
    FToken{ .Flags = { }, .TokenType = ETokenType::Debugger },                                                      // debugger
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Default },                                    // default
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Else },                                       // else
    FToken{ .Flags = { }, .TokenType = ETokenType::Finally },                                                       // finally
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Function },                                   // function
    FToken{ .Flags = { }, .TokenType = ETokenType::If },                                                            // if
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Return },                                     // return
    FToken{ .Flags = { }, .TokenType = ETokenType::Switch },                                                        // switch
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true }, .TokenType = ETokenType::Throw }, // throw
    FToken{ .Flags = { }, .TokenType = ETokenType::Try },                                                           // try
    FToken{ .Flags = { }, .TokenType = ETokenType::Var },                                                           // var
    FToken{ .Flags = { }, .TokenType = ETokenType::Const },                                                         // const
    FToken{ .Flags = { }, .TokenType = ETokenType::With },                                                          // with
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true }, .TokenType = ETokenType::New },                   // new
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::This },                                       // this
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Super },                                      // super
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Class },                                      // class
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::Extends },                                    // extends
    FToken{ .Flags = { }, .TokenType = ETokenType::Export },                                                        // export
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Import },                                     // import
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Null },                                       // null
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::True },                                       // true
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::False },                                      // false
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true }, .TokenType = ETokenType::Typeof }, // typeof
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true }, .TokenType = ETokenType::Void },  // void
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true }, .TokenType = ETokenType::Delete }, // delete
    FToken{ .Flags = { .BeforeExpr = true, .IsLoop = true }, .TokenType = ETokenType::Do },                        // do
    FToken{ .Flags = { .IsLoop = true }, .TokenType = ETokenType::For },                                            // for
    FToken{ .Flags = { .IsLoop = true }, .TokenType = ETokenType::While },                                          // while

    // Keyword-like identifiers
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::As },                                         // as
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Assert },                                     // assert
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Async },                                      // async
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Await },                                      // await
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Defer },                                      // defer
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::From },                                       // from
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Get },                                        // get
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Let },                                        // let
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Meta },                                       // meta
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Of },                                         // of
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Sent },                                       // sent
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Set },                                        // set
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Source },                                     // source
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Static },                                     // static
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Using },                                      // using
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Yield },                                      // yield

    // Flow / TS keyword-like
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Asserts },                                    // asserts
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Checks },                                     // checks
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Exports },                                    // exports
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Global },                                     // global
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Implements },                                 // implements
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Intrinsic },                                  // intrinsic
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Infer },                                      // infer
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Is },                                         // is
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Mixins },                                     // mixins
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Proto },                                      // proto
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Require },                                    // require
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Satisfies },                                  // satisfies
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Keyof },                                      // keyof
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Readonly },                                   // readonly
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Unique },                                     // unique
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Abstract },                                   // abstract
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Declare },                                    // declare
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Enum },                                       // enum
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Module },                                     // module
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Namespace },                                  // namespace
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Interface },                                  // interface
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Type },                                       // type
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Opaque },                                     // opaque

    // Literals and special
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Name },                                       // name
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Placeholder },                                // %%
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::String },                                     // string
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::Number },                                     // num
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::BigInt },                                     // bigint
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::RegExp },                                     // regexp
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::PrivateName },                                // #name
    FToken{ .Flags = { }, .TokenType = ETokenType::EndOfFile },                                                     // eof

    // JSX
    FToken{ .Flags = { }, .TokenType = ETokenType::JSXName },                                                       // jsxname
    FToken{ .Flags = { .BeforeExpr = true }, .TokenType = ETokenType::JSXText },                                    // jsxtext
    FToken{ .Flags = { .StartsExpr = true }, .TokenType = ETokenType::JSXTagStart },                                // jsxtagstart
    FToken{ .Flags = { }, .TokenType = ETokenType::JSXTagEnd },                                                     // jsxtagend
};


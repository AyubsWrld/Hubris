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
    U8      RightAssociative :  1   =   false;          // tokens associativity, defaults to left associative (false) unless otherwise specified. ( Bitfield must zero this out)
    U8      IsLoop :            1   =   false;          // whether the token implies source jumping 
    U8      Prefix :            1   =   false;          // fixity of token. note that we the flags must include both postfix and prefix for operators that can act as both ('--/++')
    U8      Postfix :           1   =   false;          // fixity of token. note that we the flags must include both postfix and prefix for operators that can act as both ('--/++')
    U8      : 2;                                        // padding bits.
};

struct FToken 
{
    
    FTokenFlags                 Flags;
    std::optional<U64>          BinOp;        // Encodes Precedence.

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
    
    constexpr bool IsIdentifier() const noexcept;
    
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
    constexpr bool KeywordOrIdentifierIsKeyword() const noexcept;
    
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
    constexpr bool IsLiteralPropertyName() const noexcept;
    
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
    constexpr bool PrefixesExpression() const noexcept;
    
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
    constexpr bool CanStartExpression() const noexcept;
    
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
    constexpr bool IsAssignment() const noexcept;
    
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
    constexpr bool IsFlowInterfaceOrTypeOrOpaque() const noexcept;
    
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
    constexpr bool IsLoop() const noexcept;
    
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
    constexpr bool IsOperator() const noexcept;
    
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
    constexpr bool IsPostfix() const noexcept;
    
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
    constexpr bool IsPrefix() const noexcept;
    
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
    constexpr bool IsTSTypeOperator() const noexcept;
    
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
    constexpr bool IsTSDeclarationStart() const noexcept;
    
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
    constexpr bool IsRightAssociative() const noexcept;
    
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
    constexpr bool operator==(const FToken& other) const;

};

// Maps tokens to their attributes. 
static inline constexpr FToken kTokenAttributes[std::to_underlying(ETokenType::_MAX_)] =
{
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true } },                              // bracketleft          [
    FToken{ .Flags = { } },                                                                      // bracketright         ]
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true } },                              // braceleft            {
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true } },                              // bracebarleft         {|
    FToken{ .Flags = { } },                                                                      // braceright           }
    FToken{ .Flags = { } },                                                                      // bracebarright        |}
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true } },                              // parenthesisleft      (
    FToken{ .Flags = { } },                                                                      // parenthesisright     )
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // comma                ,
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // semicolon            ;
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // colon                :
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // doublecolon          ::
    FToken{ .Flags = { } },                                                                      // dot                  .
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // question             ?
    FToken{ .Flags = { } },                                                                      // questiondot          ?.
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // arrow                =>
    FToken{ .Flags = { } },                                                                      // template             template
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // ellipsis             ...
    FToken{ .Flags = { .StartsExpr = true } },                                                   // backquote            `
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true } },                              // dollarbraceleft      ${
    FToken{ .Flags = { .StartsExpr = true } },                                                   // templatetail         ...`
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true } },                              // templatenontail      ...${
    FToken{ .Flags = { } },                                                                      // at                   @
    FToken{ .Flags = { .StartsExpr = true } },                                                   // hash                 #
    FToken{ .Flags = { } },                                                                      // interpreterdirective #!...

    // assignment operators
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true } },                                // eq                   =
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true } },                                // assign               _=
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true } },                                // slashassign          _=
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true } },                                // xorassign            _=
    FToken{ .Flags = { .BeforeExpr = true, .IsAssign = true } },                                // moduloassign         _=

    // unary / update operators
    FToken{ .Flags = { .StartsExpr = true, .Prefix = true, .Postfix = true } },                 // incdec               ++/--
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true } },              // bang                 !
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true } },              // tilde                ~

    // hack topic tokens
    FToken{ .Flags = { .StartsExpr = true } },                                                   // doublecaret          ^^
    FToken{ .Flags = { .StartsExpr = true } },                                                   // doubleat             @@

    // binary operators
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 0 },                                      // pipeline             |>
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 1 },                                      // nullishcoalescing    ??
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 1 },                                      // logicalor            ||
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 2 },                                      // logicaland           &&
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 3 },                                      // bitwiseor            |
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 4 },                                      // bitwisexor           ^
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 5 },                                      // bitwiseand           &
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 6 },                                      // equality             ==/!=
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 7 },                                      // lessthan             
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 7 },                                      // greaterthan          >
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 7 },                                      // relational           </>/<=/>=
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 8 },                                      // bitshift             <</>>/>>>
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 8 },                                      // bitshiftleft         
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 8 },                                      // bitshiftright        >>/>>>
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true }, .Binop = 9 },  // plusminus            +/-
    FToken{ .Flags = { .StartsExpr = true }, .Binop = 10 },                                     // modulo               %
    FToken{ .Flags = { }, .Binop = 10 },                                                         // star                 *
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 10 },                                     // slash                /
    FToken{ .Flags = { .BeforeExpr = true, .RightAssociative = true }, .Binop = 11 },           // exponent             **

    // keywords
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 7 },                                      // in                   in
    FToken{ .Flags = { .BeforeExpr = true }, .Binop = 7 },                                      // instanceof           instanceof
    FToken{ .Flags = { } },                                                                      // break                break
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // case                 case
    FToken{ .Flags = { } },                                                                      // catch                catch
    FToken{ .Flags = { } },                                                                      // continue             continue
    FToken{ .Flags = { } },                                                                      // debugger             debugger
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // default              default
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // else                 else
    FToken{ .Flags = { } },                                                                      // finally              finally
    FToken{ .Flags = { .StartsExpr = true } },                                                   // function             function
    FToken{ .Flags = { } },                                                                      // if                   if
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // return               return
    FToken{ .Flags = { } },                                                                      // switch               switch
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true } },              // throw                throw
    FToken{ .Flags = { } },                                                                      // try                  try
    FToken{ .Flags = { } },                                                                      // var                  var
    FToken{ .Flags = { } },                                                                      // const                const
    FToken{ .Flags = { } },                                                                      // with                 with
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true } },                              // new                  new
    FToken{ .Flags = { .StartsExpr = true } },                                                   // this                 this
    FToken{ .Flags = { .StartsExpr = true } },                                                   // super                super
    FToken{ .Flags = { .StartsExpr = true } },                                                   // class                class
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // extends              extends
    FToken{ .Flags = { } },                                                                      // export               export
    FToken{ .Flags = { .StartsExpr = true } },                                                   // import               import
    FToken{ .Flags = { .StartsExpr = true } },                                                   // null                 null
    FToken{ .Flags = { .StartsExpr = true } },                                                   // true                 true
    FToken{ .Flags = { .StartsExpr = true } },                                                   // false                false
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true } },              // typeof               typeof
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true } },              // void                 void
    FToken{ .Flags = { .BeforeExpr = true, .StartsExpr = true, .Prefix = true } },              // delete               delete
    FToken{ .Flags = { .BeforeExpr = true, .IsLoop = true } },                                  // do                   do
    FToken{ .Flags = { .IsLoop = true } },                                                       // for                  for
    FToken{ .Flags = { .IsLoop = true } },                                                       // while                while

    // keyword-like identifiers
    FToken{ .Flags = { .StartsExpr = true } },                                                   // as                   as
    FToken{ .Flags = { .StartsExpr = true } },                                                   // assert               assert
    FToken{ .Flags = { .StartsExpr = true } },                                                   // async                async
    FToken{ .Flags = { .StartsExpr = true } },                                                   // await                await
    FToken{ .Flags = { .StartsExpr = true } },                                                   // defer                defer
    FToken{ .Flags = { .StartsExpr = true } },                                                   // from                 from
    FToken{ .Flags = { .StartsExpr = true } },                                                   // get                  get
    FToken{ .Flags = { .StartsExpr = true } },                                                   // let                  let
    FToken{ .Flags = { .StartsExpr = true } },                                                   // meta                 meta
    FToken{ .Flags = { .StartsExpr = true } },                                                   // of                   of
    FToken{ .Flags = { .StartsExpr = true } },                                                   // sent                 sent
    FToken{ .Flags = { .StartsExpr = true } },                                                   // set                  set
    FToken{ .Flags = { .StartsExpr = true } },                                                   // source               source
    FToken{ .Flags = { .StartsExpr = true } },                                                   // static               static
    FToken{ .Flags = { .StartsExpr = true } },                                                   // using                using
    FToken{ .Flags = { .StartsExpr = true } },                                                   // yield                yield

    // flow / ts keyword-like
    FToken{ .Flags = { .StartsExpr = true } },                                                   // asserts              asserts
    FToken{ .Flags = { .StartsExpr = true } },                                                   // checks               checks
    FToken{ .Flags = { .StartsExpr = true } },                                                   // exports              exports
    FToken{ .Flags = { .StartsExpr = true } },                                                   // global               global
    FToken{ .Flags = { .StartsExpr = true } },                                                   // implements           implements
    FToken{ .Flags = { .StartsExpr = true } },                                                   // intrinsic            intrinsic
    FToken{ .Flags = { .StartsExpr = true } },                                                   // infer                infer
    FToken{ .Flags = { .StartsExpr = true } },                                                   // is                   is
    FToken{ .Flags = { .StartsExpr = true } },                                                   // mixins               mixins
    FToken{ .Flags = { .StartsExpr = true } },                                                   // proto                proto
    FToken{ .Flags = { .StartsExpr = true } },                                                   // require              require
    FToken{ .Flags = { .StartsExpr = true } },                                                   // satisfies            satisfies
    FToken{ .Flags = { .StartsExpr = true } },                                                   // keyof                keyof
    FToken{ .Flags = { .StartsExpr = true } },                                                   // readonly             readonly
    FToken{ .Flags = { .StartsExpr = true } },                                                   // unique               unique
    FToken{ .Flags = { .StartsExpr = true } },                                                   // abstract             abstract
    FToken{ .Flags = { .StartsExpr = true } },                                                   // declare              declare
    FToken{ .Flags = { .StartsExpr = true } },                                                   // enum                 enum
    FToken{ .Flags = { .StartsExpr = true } },                                                   // module               module
    FToken{ .Flags = { .StartsExpr = true } },                                                   // namespace            namespace
    FToken{ .Flags = { .StartsExpr = true } },                                                   // interface            interface
    FToken{ .Flags = { .StartsExpr = true } },                                                   // type                 type
    FToken{ .Flags = { .StartsExpr = true } },                                                   // opaque               opaque

    // literals and special
    FToken{ .Flags = { .StartsExpr = true } },                                                   // name                 name
    FToken{ .Flags = { .StartsExpr = true } },                                                   // placeholder          %%
    FToken{ .Flags = { .StartsExpr = true } },                                                   // string               string
    FToken{ .Flags = { .StartsExpr = true } },                                                   // number               num
    FToken{ .Flags = { .StartsExpr = true } },                                                   // bigint               bigint
    FToken{ .Flags = { .StartsExpr = true } },                                                   // regexp               regexp
    FToken{ .Flags = { .StartsExpr = true } },                                                   // privatename          #name
    FToken{ .Flags = { } },                                                                      // endoffile            eof

    // jsx
    FToken{ .Flags = { } },                                                                      // jsxname              jsxname
    FToken{ .Flags = { .BeforeExpr = true } },                                                   // jsxtext              jsxtext
    FToken{ .Flags = { .StartsExpr = true } },                                                   // jsxtagstart          jsxtagstart
    FToken{ .Flags = { } },                                                                      // jsxtagend            jsxtagend
};







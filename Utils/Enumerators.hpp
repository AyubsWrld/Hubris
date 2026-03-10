#pragma once
#include <type_traits>

// TODO: Shorthand for declaring bitmasks. 
#define DECLARE_BITMASK(ENUMERATOR_NAME, ...) \


// Doesn't work with ADL, study later. 
template<typename T> 
requires std::is_enum_v<T>
constexpr T operator|(T EnumeratorA, T EnumeratorB) noexcept
{
    using   TUnderlying     = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<TUnderlying>(EnumeratorA) | static_cast<TUnderlying>(EnumeratorB));
}

template<typename T> 
requires std::is_enum_v<T>
constexpr T operator&(T a, T b) noexcept {
    using U = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<U>(a) & static_cast<U>(b));
}

template<typename T> 
requires std::is_enum_v<T>
constexpr T operator^(T a, T b) noexcept {
    using U = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<U>(a) ^ static_cast<U>(b));
}

template<typename T> 
requires std::is_enum_v<T>
constexpr T operator~(T a) noexcept {
    using U = std::underlying_type_t<T>;
    return static_cast<T>(~static_cast<U>(a));
}

template<typename T> 
requires std::is_enum_v<T>
constexpr T& operator|=(T& a, T b) noexcept {
    return a = a | b;
}

template<typename T> 
requires std::is_enum_v<T>
constexpr T& operator&=(T& a, T b) noexcept {
    return a = a & b;
}

#pragma once 

#define TTYPE_TABLE                                                      \
    OP(EQ,               "=")                                            \
    OP(NOT,              "!")                                            \
    OP(GREATER,          ">")        /* compare */                       \
    OP(LESS,             "<")                                            \
                                                                         \
    OP(PLUS,             "+")        /* math */                          \
    OP(MINUS,            "-")                                            \
    OP(MULT,             "*")                                            \
    OP(DIV,              "/")                                            \
    OP(MOD,              "%")                                            \
                                                                         \
    OP(AND,              "&")        /* bit ops */                       \
    OP(OR,               "|")                                            \
    OP(XOR,              "^")                                            \
    OP(RSHIFT,           ">>")                                           \
    OP(LSHIFT,           "<<")                                           \
                                                                         \
    OP(COMPL,            "~")                                            \
                                                                         \
    OP(AND_AND,          "&&")       /* logical */                       \
    OP(OR_OR,            "||")                                           \
    OP(QUERY,            "?")                                            \
    OP(COLON,            ":")                                            \
                                                                         \
    OP(COMMA,            ",")        /* grouping */                      \
    OP(OPEN_PAREN,       "(")                                            \
    OP(CLOSE_PAREN,      ")")                                            \
                                                                         \
    TK(EOF,              NONE)                                           \
                                                                         \
    OP(EQ_EQ,            "==")       /* compare */                       \
    OP(NOT_EQ,           "!=")                                           \
    OP(GREATER_EQ,       ">=")                                           \
    OP(LESS_EQ,          "<=")                                           \
    OP(SPACESHIP,        "<=>")                                          \
                                                                         \
    /* Unary + / - in preprocessor expressions */                        \
    OP(PLUS_EQ,          "+=")       /* math */                          \
    OP(MINUS_EQ,         "-=")                                           \
                                                                         \
    OP(MULT_EQ,          "*=")                                           \
    OP(DIV_EQ,           "/=")                                           \
    OP(MOD_EQ,           "%=")                                           \
                                                                         \
    OP(AND_EQ,           "&=")       /* bit ops */                       \
    OP(OR_EQ,            "|=")                                           \
    OP(XOR_EQ,           "^=")                                           \
    OP(RSHIFT_EQ,        ">>=")                                          \
    OP(LSHIFT_EQ,        "<<=")                                          \
                                                                         \
    /* Digraphs */                                                       \
    OP(HASH,             "#")        /* digraphs */                      \
    OP(PASTE,            "##")                                           \
    OP(OPEN_SQUARE,      "[")                                            \
    OP(CLOSE_SQUARE,     "]")                                            \
    OP(OPEN_BRACE,       "{")                                            \
    OP(CLOSE_BRACE,      "}")                                            \
    OP(OPEN_SPLICE,      "[:")                                           \
    OP(CLOSE_SPLICE,     ":]")                                           \
                                                                         \
    /* Remaining punctuation */                                          \
    OP(SEMICOLON,        ";")        /* structure */                     \
    OP(ELLIPSIS,         "...")                                          \
                                                                         \
    OP(PLUS_PLUS,        "++")       /* increment */                     \
    OP(MINUS_MINUS,      "--")                                           \
                                                                         \
    OP(DEREF,            "->")       /* accessors */                     \
    OP(DOT,              ".")                                            \
    OP(SCOPE,            "::")                                           \
    OP(DEREF_STAR,       "->*")                                          \
    OP(DOT_STAR,         ".*")                                           \
                                                                         \
    OP(REFLECT_OP,       "^^")                                           \
    OP(ATSIGN,           "@")        /* Objective-C */                   \
                                                                         \
    /* Identifiers */                                                    \
    TK(NAME,             IDENT)      /* word */                          \
    TK(AT_NAME,          IDENT)      /* @word - Objective-C */           \
                                                                         \
    /* Numbers */                                                        \
    TK(NUMBER,           LITERAL)    /* 34_be+ta */                      \
                                                                         \
    /* Character literals */                                             \
    TK(CHAR,             LITERAL)    /* 'char' */                        \
    TK(WCHAR,            LITERAL)    /* L'char' */                       \
    TK(CHAR16,           LITERAL)    /* u'char' */                       \
    TK(CHAR32,           LITERAL)    /* U'char' */                       \
    TK(UTF8CHAR,         LITERAL)    /* u8'char' */                      \
                                                                         \
    TK(OTHER,            LITERAL)    /* stray punctuation */             \
                                                                         \
    /* String literals */                                                \
    TK(STRING,           LITERAL)    /* "string" */                      \
    TK(WSTRING,          LITERAL)    /* L"string" */                     \
    TK(STRING16,         LITERAL)    /* u"string" */                     \
    TK(STRING32,         LITERAL)    /* U"string" */                     \
    TK(UTF8STRING,       LITERAL)    /* u8"string" */                    \
                                                                         \
    TK(OBJC_STRING,      LITERAL)    /* @"string" */                     \
    TK(HEADER_NAME,      LITERAL)    /* <stdio.h> in #include */         \
    TK(UNEVAL_STRING,    LITERAL)    /* C++26 */                         \
                                                                         \
    /* User-defined literals */                                          \
    TK(CHAR_USERDEF,         LITERAL)                                    \
    TK(WCHAR_USERDEF,        LITERAL)                                    \
    TK(CHAR16_USERDEF,       LITERAL)                                    \
    TK(CHAR32_USERDEF,       LITERAL)                                    \
    TK(UTF8CHAR_USERDEF,     LITERAL)                                    \
                                                                         \
    TK(STRING_USERDEF,       LITERAL)                                    \
    TK(WSTRING_USERDEF,      LITERAL)                                    \
    TK(STRING16_USERDEF,     LITERAL)                                    \
    TK(STRING32_USERDEF,     LITERAL)                                    \
    TK(UTF8STRING_USERDEF,   LITERAL)                                    \
                                                                         \
    TK(EMBED,           LITERAL)    /* #embed - C23 */                   \
                                                                         \
    TK(COMMENT,         LITERAL)    /* Only if output comments */        \
                                                                         \
    TK(MACRO_ARG,       NONE)       /* Macro argument */                 \
    TK(PRAGMA,          NONE)       /* Deferred pragma */                \
    TK(PRAGMA_EOL,      NONE)       /* End-of-line for deferred pragmas*/\
    TK(PADDING,         NONE)       /* Whitespace for -E */

#define OP(e, s) CPP_ ## e,
#define TK(e, s) CPP_ ## e,

enum class TokenType 
{
    TTYPE_TABLE
};

#undef OP
#undef TK

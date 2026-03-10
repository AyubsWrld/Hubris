/*
   ================================================================================================================
                                                    FILE OVERVIEW
   ================================================================================================================

   @file:               Options.hpp

   @purpose:            Defines the 

   @token-design:

        The assignment of fine-grained, information-carrying token type objects allows the
        tokenizer to store contextual information about tokens in a form that is extremely
        cheap for the parser to query during parsing.


   @design:             Token classification is implemented using lightweight constexpr

   @usage:              Tokens are produced by the tokenizer during lexical scanning of

   @notes:              This file does not perform lexical analysis itself. It only defines

   ================================================================================================================
*/


/* 
    @note:  Bitwise operations work during enumerator definitions regardless
            of whether or not the enumeration they are part of is scoped/unscoped.
            
        enum class Scoped : std::uint8_t
        {
            First   = (1 << 0), 
            Second  = (1 << 1),
            Mix     = First | Second, // ok
        };

        enum Unscoped : std::uint8_t
        {
            First   = (1 << 0), 
            Second  = (1 << 1),
            Mix     = First | Second,
        };

        Scoped::First | Scoped::Second // invalid, operator| expects two integral operands.
*/

#pragma once

enum class ScopeFlag 
{
    OTHER           = (1 << 0),
    PROGRAM         = (1 << 0),
    FUNCTION_BASE   = (1 << 1),
    ARROW           = (1 << 2),
    SIMPLE_CATCH    = (1 << 3),
    SUPER           = (1 << 4),
    DIRECT_SUPER    = (1 << 5),
    CLASS_BASE      = (1 << 6),
    STATIC_BLOCK    = (1 << 7),
    SWITCH          = (1 << 8),
    NEW_TARGET      = (1 << 9),
    TS_MODULE       = (1 << 10),
    FUNCTION        = FUNCTION_BASE | NEW_TARGET,
    CLASS           = CLASS_BASE | NEW_TARGET,
    VAR             = PROGRAM | FUNCTION | STATIC_BLOCK | TS_MODULE
};

enum class BindingFlag : unsigned int
{

    KIND_VALUE             = (1 << 0),
    KIND_TYPE              = (1 << 1),

    SCOPE_VAR              = (1 << 2),  // var-style binding
    SCOPE_LEXICAL          = (1 << 3),  // let- or const-style binding
    SCOPE_FUNCTION         = (1 << 4),  // function declaration
    SCOPE_OUTSIDE          = (1 << 5),  // special case for function names bound inside the function

    // Misc flags
    FLAG_NONE              = (1 << 6),
    FLAG_CLASS             = (1 << 7),
    FLAG_TS_ENUM           = (1 << 8),
    FLAG_TS_CONST_ENUM     = (1 << 9),
    FLAG_TS_EXPORT_ONLY    = (1 << 10),
    FLAG_FLOW_DECLARE_FN   = (1 << 11),
    FLAG_TS_IMPORT         = (1 << 12),
    FLAG_NO_LET_IN_LEXICAL = (1 << 13),

    /*                   = is value?  | is type?  |      scope     |    misc flags    */

    TYPE_CLASS           = KIND_VALUE | KIND_TYPE | SCOPE_LEXICAL  | FLAG_CLASS | FLAG_NO_LET_IN_LEXICAL,
    TYPE_LEXICAL         = KIND_VALUE | SCOPE_LEXICAL | FLAG_NO_LET_IN_LEXICAL,
    TYPE_CATCH_PARAM     = KIND_VALUE | SCOPE_LEXICAL,
    TYPE_VAR             = KIND_VALUE | SCOPE_VAR,
    TYPE_FUNCTION        = KIND_VALUE | SCOPE_FUNCTION,
    TYPE_TS_INTERFACE    = KIND_TYPE  | FLAG_CLASS,
    TYPE_TS_TYPE         = KIND_TYPE,
    TYPE_TS_ENUM         = KIND_VALUE | KIND_TYPE | SCOPE_LEXICAL | FLAG_TS_ENUM | FLAG_NO_LET_IN_LEXICAL,
    TYPE_TS_AMBIENT      = FLAG_TS_EXPORT_ONLY,

    // these bindings don't introduce anything in the scope.
    TYPE_NONE            = FLAG_NONE,
    TYPE_OUTSIDE         = KIND_VALUE | FLAG_NONE,
    TYPE_TS_CONST_ENUM   = TYPE_TS_ENUM | FLAG_TS_CONST_ENUM,
    TYPE_TS_NAMESPACE    = FLAG_TS_EXPORT_ONLY,
    TYPE_TS_TYPE_IMPORT  = KIND_TYPE | FLAG_TS_IMPORT,
    TYPE_TS_VALUE_IMPORT = FLAG_TS_IMPORT,
    TYPE_FLOW_DECLARE_FN = FLAG_FLOW_DECLARE_FN
};

enum class ClassElementType 
{
    OTHER           = (1 << 0),
    FLAG_STATIC     = (1 << 1),
    KIND_GETTER     = (1 << 2),
    KIND_SETTER     = (1 << 3),
    KIND_ACCESSOR   = KIND_GETTER | KIND_SETTER,
    STATIC_GETTER   = FLAG_STATIC | KIND_GETTER,
    STATIC_SETTER   = FLAG_STATIC | KIND_SETTER,
    INSTANCE_GETTER = KIND_GETTER,
    INSTANCE_SETTER = KIND_SETTER,
};

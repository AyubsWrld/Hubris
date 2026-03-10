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

#pragma once
#include "Options.hpp"
#include "Scope.hpp"
#include <string>

class UParserBase 
{
    // Per babel.
    // declare options: Options;
    // declare optionFlags: OptionFlags;
    // declare inModule: boolean;
    // declare scope: ScopeHandler<any>;
    // declare classScope: ClassScopeHandler;
    // declare prodParam: ProductionParameterHandler;
    // declare expressionScope: ExpressionScopeHandler;
    // declare plugins: PluginsMap;
    // declare filename: string | undefined | null;
    // declare startIndex: number;

    FCompilerOptions    Options;
    EOptionFlags        OptionFlags;
    bool                bInModule;
};


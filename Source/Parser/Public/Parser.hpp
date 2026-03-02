#pragma once
#include "Options.hpp"
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

    FParserOptions Options;
    enum {
        __UNIMPLEMENTED__
    } OptionFlags;
    bool bInModule;
};

class UParser
{
public:

    void ReadFile(std::string);
};

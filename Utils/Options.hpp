#pragma once 
#include <optional>
#include "ShorthandTypes.hpp"

enum class ESourceType 
{
    Script,
    CommonJS,
    Module,
    Unambiguous,
    _MAX_
};

enum class FOptionFlags : U16
{
    AllowAwaitOutsideFunction = 1u << 0,
    AllowReturnOutsideFunction = 1u << 1,
    AllowNewTargetOutsideFunction = 1u << 2,
    AllowImportExportEverywhere = 1u << 3,
    AllowSuperOutsideMethod = 1u << 4,
    AllowYieldOutsideFunction = 1u << 5,
    AllowUndeclaredExports = 1u << 6,
    Ranges = 1u << 7,
    Tokens = 1u << 8,
    CreateImportExpressions = 1u << 9,
    CreateParenthesizedExpressions = 1u << 10,
    ErrorRecovery = 1u << 11,
    AttachComment = 1u << 12,
    AnnexB = 1u << 13,
    _MAX_
};

enum class EKeepOptionalKeys 
{
    SoureFilename,
    StrictMode,
    _MAX_
};


union UPlugin 
{
};

struct FCompilerOptions
{
    /**
     * By default, import and export declarations can only appear at a program's top level.
     * Setting this option to true allows them anywhere where a statement is allowed.
     */
    std::optional<bool> bAllowImportExportEverywhere;

    /**
     * By default, await use is not allowed outside of an async function.
     * Set this to true to accept such code.
     */
    std::optional<bool> bAllowAwaitOutsideFunction;

    /**
     * By default, a return statement at the top level raises an error.
     * Set this to true to accept such code.
     */
    std::optional<bool> bAllowReturnOutsideFunction;

    /**
     * By default, new.target use is not allowed outside of a function or class.
     * Set this to true to accept such code.
     */
    std::optional<bool> bAllowNewTargetOutsideFunction;

    /**
     * By default, super calls are not allowed outside of a method.
     * Set this to true to accept such code.
     */
    std::optional<bool> bAllowSuperOutsideMethod;

    /**
     * By default, exported identifiers must refer to a declared variable.
     * Set this to true to allow export statements to reference undeclared variables.
     */
    std::optional<bool> bAllowUndeclaredExports;

    /**
     * By default, yield use is not allowed outside of a generator function.
     * Set this to true to accept such code.
     */
    std::optional<bool> bAllowYieldOutsideFunction;

    /**
     * By default, the parser parses JavaScript code according to Annex B syntax.
     * Set this to false to disable such behavior.
     */
    std::optional<bool> bAnnexB;

    /**
     * By default, the parser attaches comments to adjacent AST nodes.
     * When this option is set to false, comments are not attached.
     * It can provide up to 30% performance improvement when the input code has many comments.
     * It is not recommended to use bAttachComment = false with transforms,
     * as doing so removes all the comments in output code, and renders annotations such as
     * / * istanbul ignore next * / nonfunctional.
     */
    std::optional<bool> bAttachComment;

    /**
     * By default, the parser always throws an error when it finds some invalid code.
     * When this option is set to true, it will store the parsing error and
     * try to continue parsing the invalid input file.
     */
    std::optional<bool> bErrorRecovery;

    /**
     * Indicate the mode the code should be parsed in.
     * Can be one of Script, CommonJS, Module, or Unambiguous. Defaults to Script.
     * Unambiguous will make the parser attempt to guess, based on the presence
     * of ES6 import or export statements.
     * Files with ES6 imports and exports are considered Module and are otherwise Script.
     *
     * Use CommonJS to parse code intended to be run in a CommonJS environment such as Node.js.
     */
    std::optional<ESourceType> SourceType;

    /**
     * Correlate output AST nodes with their source filename.
     * Useful when generating code and source maps from the ASTs of multiple input files.
     */
    std::optional<std::string> SourceFilename;

    /**
     * By default, all source indexes start from 0.
     * You can provide a start index to alternatively start with.
     * Useful for integration with other source tools.
     */
    std::optional<I32> StartIndex;

    /**
     * By default, the first line of code parsed is treated as line 1.
     * You can provide a line number to alternatively start with.
     * Useful for integration with other source tools.
     */
    std::optional<I32> StartLine;

    /**
     * By default, the parsed code is treated as if it starts from line 1, column 0.
     * You can provide a column number to alternatively start with.
     * Useful for integration with other source tools.
     */
    std::optional<I32> StartColumn;

    /**
     * Array containing the plugins that you want to enable.
     */
    
    //std::optional<std::vector<UPlugin>> Plugins; // TODO: Tidy this. 

    /**
     * Should the parser work in strict mode.
     * Defaults to true if SourceType == Module. Otherwise, false.
     */
    std::optional<bool> bStrictMode;

    /**
     * Adds a ranges property to each node: [node.start, node.end]
     */
    std::optional<bool> bRanges;

    /**
     * Adds all parsed tokens to a tokens property on the File node.
     */
    std::optional<bool> bTokens;

    /**
     * By default, the parser adds information about parentheses by setting
     * extra.parenthesized to true as needed.
     * When this option is true the parser creates ParenthesizedExpression  
     * AST nodes instead of using the extra property.
     */
    std::optional<bool> bCreateParenthesizedExpressions;

    /**
     * By default, the parser parses import expressions as an ImportExpression node.
     * Set this to false to parse it as CallExpression(Import, [Identifier(foo)]).
     */
    
    std::optional<bool> bCreateImportExpressions;


};

inline FCompilerOptions CreateDefaultOptions()
{
    return FCompilerOptions{
        .bAllowImportExportEverywhere       = false,
        .bAllowAwaitOutsideFunction         = false,
        .bAllowReturnOutsideFunction        = false,
        .bAllowNewTargetOutsideFunction     = false,
        .bAllowSuperOutsideMethod           = false,
        .bAllowUndeclaredExports            = false,
        .bAllowYieldOutsideFunction         = false,

        .bAnnexB                            = true,
        .bAttachComment                     = true,
        .bErrorRecovery                     = false,

        .SourceType                         = ESourceType::Script,
        .SourceFilename                     = std::optional<std::string>{},

        .StartIndex                         = 0,
        .StartLine                          = 1,
        .StartColumn                        = 0,

        //.Plugins                          = std::vector<UPlugin>{}, // TODO

        .bStrictMode                        = std::optional<bool>{},

        .bRanges                            = false,
        .bTokens                            = false,

        .bCreateParenthesizedExpressions    = false,
        .bCreateImportExpressions           = true
    };
}

inline FCompilerOptions GetOptions()
{
    FCompilerOptions Options = CreateDefaultOptions();
    return Options;
}

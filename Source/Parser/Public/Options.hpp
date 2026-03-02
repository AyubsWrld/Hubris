#pragma once 
#include <optional>
#include <vector>
#include "ShorthandTypes.hpp"

enum class ESourceType {
    Script,
    CommonJS,
    Module,
    Unambiguous
};

union UPlugin 
{
    /* See babel. 
    export type ParserPluginWithOptions =
    | ["discardBinding", { syntaxType: "void" }]
    | ["estree", { classFeatures?: boolean }]
    | ["optionalChainingAssign", { version: "2023-07" }]
    | ["partialApplication", PartialApplicationPluginOptions]
    | ["pipelineOperator", PipelineOperatorPluginOptions]
    | ["flow", FlowPluginOptions]
    | ["typescript", TypeScriptPluginOptions];
    */
};

struct FParserOptions
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
    std::optional<std::vector<UPlugin>> Plugins; // TODO: Tidy this. 

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

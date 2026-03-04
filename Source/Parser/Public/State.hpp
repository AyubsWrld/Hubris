#pragma once 
#include "ShorthandTypes.hpp"
#include "SourceLocation.hpp"
#include <optional>
#include <vector>

using   TokenType   =   U64;

enum class LoopLabelKind 
{
    Loop,
    Switch,
    _MAX_
};
class FState 
{
    FPosition StartLocation;
    FPosition EndLocation;


    // position information for the previous token
    // this is initialized when generating the second token.
    std::optional<FPosition> LastTokenEndLocation;
    
    // this is initialized when generating the second token.
    std::optional<FPosition> LastTokenStartLocation;

    U64 StartIndex;
    U64 CurrentLine;
    U64 Position;
    U64 LineStart;
    U64 PotentialArrowAt; // used to signify the start of a potential arrow function
    U64 CommentsLen;
    // Used to signify the start of an expression which looks like a
    // typed arrow function, but it isn't
    // e.g. a ? (b) : c => d
    std::vector<U64> NoArrowAt;


    // Used to signify the start of an expression whose params, if it looks like
    // an arrow function, shouldn't be converted to assignable nodes.
    // This is used to defer the validation of typed arrow functions inside
    // conditional expressions.
    // e.g. a ? (b) : c => d
    //          ^
    std::vector<U64> NoArrowParamsConversionAt;

    struct 
    {
        LoopLabelKind       Kind;
        std::string         Name;
        std::optional<U64>  StatementStart;
    } Labels;


    struct
    {
        unsigned short bInType : 1;
        unsigned short bNoAnonFunctionType : 1;
        unsigned short bHasFlowComment : 1;
        unsigned short bIsAmbientContext : 1;
        unsigned short bInAbstractClass : 1;
        unsigned short bInDisallowConditionalTypesContext : 1;
        unsigned short bInConditionalConsequent : 1;

        // Hack-style pipeline plugin
        unsigned short bInHackPipelineBody : 1;
        unsigned short bSeenTopicReference : 1;
        unsigned short bCanStartJSXElement : 1;

        // word parsing flags
        unsigned short bContainsEsc : 1;
        unsigned short bHasTopLevelAwait : 1;
        unsigned short _PAD_ : 4;
    } Flags;

    FPosition CurrentPosition(); 
};

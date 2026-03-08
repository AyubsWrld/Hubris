/*
 
   ================================================================================================================
                                                    FILE OVERVIEW
   ================================================================================================================

   @author              Ayub M

   @file:               Context.hpp

   @purpose:            Defines 

   @design:             design


   @usage:              usage

   @notes:              notes

   ================================================================================================================

*/

#pragma once
#include <string>
#include <unordered_map>

struct FTokenContext
{
    bool            bPreserveSpace;
    std::string     Token;


    FTokenContext(const FTokenContext&) = default;
    FTokenContext& operator=(const FTokenContext&) = default;

    FTokenContext(FTokenContext&&) = default;
    FTokenContext& operator=(FTokenContext&&) = default;

    FTokenContext(std::string InToken, bool bInPreserveSpace);

};


enum class ETokenContextLiteral
{ 
    Brace,
    JSXOpenTag,
    JSXCloseTag,
    JSXExpression,
    _MAX_
};

static inline const std::unordered_map<ETokenContextLiteral, FTokenContext> TokenMap = 
{
    { ETokenContextLiteral::Brace, FTokenContext{"{", false} },                         // normal JavaScript expression
    { ETokenContextLiteral::JSXOpenTag, FTokenContext{"<tag", false} },                 // JSX opening tag
    { ETokenContextLiteral::JSXCloseTag, FTokenContext{"</tag", false} },               // JSX closing tag
    { ETokenContextLiteral::JSXExpression, FTokenContext{"<tag>...</tag>", true} },     // JSX expressions
};

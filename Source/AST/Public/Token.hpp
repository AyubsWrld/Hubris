#pragma once
#include "ShorthandTypes.hpp"

// export class Token {
//   constructor(state: State) {
//     const startIndex = state.startIndex || 0;
//     this.type = state.type;
//     this.value = state.value;
//     this.start = startIndex + state.start;
//     this.end = startIndex + state.end;
//     this.loc = new SourceLocation(state.startLoc, state.endLoc);
//   }
//
//   declare type: TokenType;
//   declare value: any;
//   declare start: number;
//   declare end: number;
//   declare loc: SourceLocation;
// }

using __STUB_TYPE_ = void*; 

struct Token 
{
    __STUB_TYPE_    Type;
    __STUB_TYPE_    Value;
    U64             Start;

//   declare value: any;
//   declare start: number;
//   declare end: number;
//   declare loc: SourceLocation;
};

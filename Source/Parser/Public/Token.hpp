#pragma once 

/*
struct Token
{
    TokenType      Type;
    std::any       Value;
    std::uint64_t  Start;
    std::uint64_t  End;
    SourceLocation Loc;

    explicit Token(const State& state)
        : Type(state.Type),
          Value(state.Value),
          Start((state.StartIndex.has_value() ? state.StartIndex.value() : 0ULL) + state.Start),
          End((state.StartIndex.has_value() ? state.StartIndex.value() : 0ULL) + state.End),
          Loc(state.StartLoc, state.EndLoc)
    {
    }
};
*/

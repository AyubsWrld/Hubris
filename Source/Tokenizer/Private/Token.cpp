#include "Token.hpp"
#include <utility>


const FToken& GetTokenAttributes(ETokenType InToken)
{
    return kTokenAttributes[std::to_underlying(InToken)];
}

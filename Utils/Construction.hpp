#pragma once
#include <print>

#define STUB_INVOCATION() \
    do{ std::print("[{}:{}] STUB INVOKED\n", __FUNCTION__, __LINE__); }while(false)


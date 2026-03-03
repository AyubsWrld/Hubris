#pragma once
#include <string>
#include <vector>
#include <utility>
#include <cstdint>

#ifndef NODISCARD 
#define NODISCARD [[nodiscard("The result of this expression should not be ignored.")]]
#endif

using   FString =   std::string;
using   U8      =   std::uint8_t;
using   U16     =   std::uint16_t;
using   U32     =   std::uint32_t;
using   U64     =   std::uint64_t;

using   I8      =   std::int8_t;
using   I16     =   std::int16_t;
using   I32     =   std::int32_t;
using   I64     =   std::int64_t;

using   F32     =   float;
using   F64     =   double;


using   NumericRange    =   std::pair<U64, U64>;

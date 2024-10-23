#pragma once
#include <string>
#include <cstdint>

namespace MD5Modified
{
using WordTable = std::uint32_t[4];

void MD5HashNonPadded(const WordTable h0, const std::uint32_t* msg, WordTable h);

} // namespace MD5Modified
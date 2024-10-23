#pragma once
#include <string>
#include <cstdint>

namespace MD5Modified
{
using WordTable = std::uint32_t[4];

void MD5HashPadded(std::string msg, WordTable h);
void MD5HashNonPadded(const std::uint8_t* msg, WordTable h, const WordTable h0, int grps = 8);

} // namespace MD5Modified
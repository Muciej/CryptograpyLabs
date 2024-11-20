#pragma once
#include "md5Utils.hpp"
#include <string>

namespace MD5Modified
{

void MD5HashNonPadded(const WordTable h0, const std::uint32_t* msg, WordTable h);

} // namespace MD5Modified
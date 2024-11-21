#pragma once

#include <cstdint>
#include <MD5Modified/md5MessageModification.hpp>

using std::uint32_t;

namespace MD5Modified::MessageModification
{

void overwriteBytes(uint32_t& modified, const uint32_t& abcd, const uint32_t& mask)
{
    // TODO
}

} // namespace MD5Modified::MessageModification

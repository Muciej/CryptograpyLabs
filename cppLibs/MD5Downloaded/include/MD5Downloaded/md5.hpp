#pragma once
#include <string>

namespace MD5Downloaded
{

std::string GetMD5String(std::string msg);
unsigned* MD5Hash(std::string msg);

} // namespace MD5Downloaded
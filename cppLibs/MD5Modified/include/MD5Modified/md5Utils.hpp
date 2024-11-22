#pragma once
#include <cstdint>

namespace MD5Modified
{

using WordTable = std::uint32_t[4];
using std::uint32_t;

namespace utils
{

void getWordDifference(const WordTable a, const WordTable b, WordTable& difference);
void getMessageDifference(const uint32_t* msgA, const uint32_t* msgB, uint32_t* difference);
bool compareWords(const WordTable word1, const WordTable word2);
bool compareMessages(const uint32_t* msgA, const uint32_t* msgB);
void printWord(const WordTable w);
void printMessage(const uint32_t* msg);

}

} // namespace MD5Modified
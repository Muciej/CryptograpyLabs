#include "helpers.hpp"
#include <cstdint>
#include <iostream>
#include <iomanip>

namespace testHelpers
{

bool compareWords(Word word1, Word word2)
{
    auto areEqual = true;
    for(int i = 0; i<4; i++)
    {
        if(word1[i] != word2[i])
        {
            areEqual = false;
        }
    }
    return areEqual;
}

void printWord(Word w)
{
    for(int i = 0; i<4; i++)
    {
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::hex << w[i] << ", ";
    }
    std::cout << std::dec;
    std::cout << std::endl;
}

}
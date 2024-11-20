#include <MD5Modified/md5Utils.hpp>
#include <iostream>
#include <iomanip>

namespace MD5Modified::utils
{

void getWordDifference(const WordTable a, const WordTable b, WordTable& difference)
{
    for(int i = 0; i < wordLen; i++)
    {
        difference[i] = a[i] - b[i];
    }
}

void getMessageDifference(const uint32_t* msgA, const uint32_t* msgB, uint32_t* difference)
{
    for(int i = 0; i < 16; i++)
    {
        difference[i] = msgA[i] - msgB[i];
    }
}

bool compareWords(const WordTable word1, const WordTable word2)
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

bool compareMessages(const uint32_t* msgA, const uint32_t* msgB)
{
    auto areEqual = true;
    for(int i = 0; i<16; i++)
    {
        if(msgA[i] != msgB[i])
        {
            areEqual = false;
        }
    }
    return areEqual; 
}

void printWord(const WordTable w)
{
    for(int i = 0; i<4; i++)
    {
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::hex << w[i] << ", ";
    }
    std::cout << std::dec;
    std::cout << std::endl;
}

void printMessage(const uint32_t* msg)
{
    for(int i = 0; i < 16; i++)
    {
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::hex << msg[i] << ", ";
    }
    std::cout << std::dec;
    std::cout << std::endl;
}

}
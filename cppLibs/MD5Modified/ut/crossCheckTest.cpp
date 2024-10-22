#include <gtest/gtest.h>
#include <MD5Downloaded/md5.hpp>
#include <MD5Modified/md5.hpp>
#include <string>
#include <functional>
#include <cstdint>
#include <iostream>
#include <iomanip> 

namespace
{

const auto repeats = 10000;

template <typename F, typename... Args>
int64_t measureTime(F&& func, Args&&... args)
{
    int64_t average = 0;
    for(int i = 0; i < repeats; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        average += duration.count();
    }
    return average / repeats;
}

using Word = std::uint32_t[4];

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

TEST(MD5CrossCheck, basicHash)
{
    std::string msg = "TestMsg";
    auto hashOrg = MD5Downloaded::MD5Hash(msg);
    auto hashMod = MD5Modified::MD5Hash(msg);
    EXPECT_TRUE(compareWords(hashOrg, hashMod));
    printWord(hashMod);

    msg = "HondaSzybszaNizWyglada";
    hashOrg = MD5Downloaded::MD5Hash(msg);
    hashMod = MD5Modified::MD5Hash(msg);
    EXPECT_TRUE(compareWords(hashOrg, hashMod));
    printWord(hashMod);

    msg = "298502hsdfkjglkvbo2i3q4fuqofhslvkbiq2u3yf0q98273fqi23bflkjdbvlzkjdw3";
    hashOrg = MD5Downloaded::MD5Hash(msg);
    hashMod = MD5Modified::MD5Hash(msg);
    EXPECT_TRUE(compareWords(hashOrg, hashMod));
    printWord(hashMod);


}

TEST(MD5CrossCheck, speedDifference)
{
    const std::string msg = "TestMsg";
    const auto timeOrg = measureTime(MD5Downloaded::MD5Hash, msg);
    const auto timeMod = measureTime(MD5Modified::MD5Hash, msg);
    std::cout << "Original: " << timeOrg << " ns" << std::endl;
    std::cout << "Modified: " << timeMod << " ns" << std::endl;
}

TEST(TypeTest, typeSizeCheck)
{
    std::cout << "unsigned: " << 8 * sizeof(unsigned) << std::endl;
    std::cout << "unsigned char: " << 8 * sizeof(unsigned char) << std::endl;
    std::cout << "short: " << 8 * sizeof(short) << std::endl;
    std::cout << "long: " << 8 * sizeof(long) << std::endl;
}

} // namespace

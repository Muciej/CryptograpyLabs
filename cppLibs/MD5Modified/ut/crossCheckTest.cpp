#include <gtest/gtest.h>
#include <MD5Downloaded/md5.hpp>
#include <MD5Modified/md5.hpp>
#include <string>
#include <cstdint>
#include <iostream>
#include "helpers.hpp"

namespace
{

using namespace testHelpers;

TEST(MD5CrossCheck, basicHash)
{
    std::string msg = "TestMsg";
    auto hashOrg = MD5Downloaded::MD5Hash(msg);
    MD5Modified::WordTable hashMod;
    MD5Modified::MD5HashPadded(msg, hashMod);
    EXPECT_TRUE(compareWords(hashOrg, hashMod));
    printWord(hashMod);
    printWord(hashOrg);

    msg = "HondaSzybszaNizWyglada";
    hashOrg = MD5Downloaded::MD5Hash(msg);
    MD5Modified::MD5HashPadded(msg, hashMod);
    EXPECT_TRUE(compareWords(hashOrg, hashMod));
    printWord(hashMod);

    msg = "298502hsdfkjglkvbo2i3q4fuqofhslvkbiq2u3yf0q98273fqi23bflkjdbvlzkjdw3";
    hashOrg = MD5Downloaded::MD5Hash(msg);
    MD5Modified::MD5HashPadded(msg, hashMod);
    EXPECT_TRUE(compareWords(hashOrg, hashMod));
    printWord(hashMod);
}

TEST(MD5CrossCheck, speedDifference)
{
    const std::string msg = "TestMsg";
    const auto timeOrg = measureTime(MD5Downloaded::MD5Hash, msg);
    MD5Modified::WordTable h;
    const auto timeMod = measureTime(MD5Modified::MD5HashPadded, msg, h);
    std::cout << "Original: " << timeOrg << " ns" << std::endl;
    std::cout << "Modified: " << timeMod << " ns" << std::endl;
}

TEST(TypeTest, typeSizeCheck)
{
    std::cout << "unsigned: " << 8 * sizeof(unsigned) << std::endl;
    std::cout << "unsigned char: " << 8 * sizeof(unsigned char) << std::endl;
    std::cout << "short: " << 8 * sizeof(short) << std::endl;
    std::cout << "long: " << 8 * sizeof(long) << std::endl;
    std::cout << "char: " << 8 * sizeof(char) << std::endl;
}

} // namespace

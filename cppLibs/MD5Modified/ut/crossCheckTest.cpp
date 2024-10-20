#include <gtest/gtest.h>
#include <MD5Downloaded/md5.hpp>
#include <MD5Modified/md5.hpp>
#include <string>
#include <functional>
#include <cstdint>
#include <iostream>

namespace
{

const auto repeats = 1000;

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
        average += duration.count() / repeats;
    }
    return average;
}

TEST(MD5CrossCheck, basicHash)
{
    const std::string msg = "TestMsg";
    const auto hashOrg = MD5Downloaded::GetMD5String(msg);
    const auto hashMod = MD5Modified::GetMD5String(msg);
    EXPECT_EQ(hashOrg, hashMod);
}

TEST(MD5CrossCheck, speedDifference)
{
    const std::string msg = "TestMsg";
    const auto timeOrg = measureTime(MD5Downloaded::GetMD5String, msg);
    const auto timeMod = measureTime(MD5Modified::GetMD5String, msg);
    std::cout << "Original: " << timeOrg << std::endl;
    std::cout << "Modified: " << timeMod << std::endl;
}

} // namespace

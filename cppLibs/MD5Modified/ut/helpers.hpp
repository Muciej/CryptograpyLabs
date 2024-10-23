#pragma once
#include <cstdint>
#include <functional>
#include <chrono>

namespace testHelpers
{

using Word = std::uint32_t[4];

const auto repeats = 10000;

bool compareWords(const Word word1, const Word word2);
void printWord(const Word w);

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

} // namespace testHelpers
#pragma once
#include <cstdint>
#include <functional>
#include <chrono>

namespace testHelpers
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

} // namespace testHelpers
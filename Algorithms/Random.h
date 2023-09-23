#pragma once

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

namespace th
{
namespace Random
{
    template<typename T>
    T generateWithin(const T lowerBound,
                     const T upperBound)
    {
        std::random_device seed; // Will be used to obtain a seed for the random number engine
        std::mt19937       mt(seed());

        std::uniform_int_distribution<T> idist(lowerBound, upperBound);

        return idist(mt);
    }

    template<typename T>
    void shuffle(std::vector<T>& elements)
    {
        unsigned seed   = std::chrono::system_clock::now().time_since_epoch().count();
        auto     engine = std::default_random_engine { seed };

        std::shuffle(elements.begin(), elements.end(), engine);
    }

} // namespace Random
} // namespace th
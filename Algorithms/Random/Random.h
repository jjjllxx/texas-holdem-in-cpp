#pragma once

#include <vector>

namespace th
{
struct PokerCard;

namespace Random
{
    int32_t generateWithin(const int32_t lowerBound,
                           const int32_t upperBound);

    void shuffle(std::vector<th::PokerCard>& cards);

    template<typename T>
    void shuffle(std::vector<T>& elements);

} // namespace Random
} // namespace th
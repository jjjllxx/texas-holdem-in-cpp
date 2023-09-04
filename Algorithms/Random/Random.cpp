#include "Random.h"

#include "Entity/Card/PokerCard.h"

#include <algorithm>
#include <chrono>
#include <random>

int32_t th::Random::generateWithin(const int32_t lowerBound,
                                   const int32_t upperBound)
{
    std::random_device seed; // Will be used to obtain a seed for the random number engine
    std::mt19937       mt(seed());

    std::uniform_int_distribution<int32_t> idist(lowerBound, upperBound);

    return idist(mt);
}

void th::Random::shuffle(std::vector<th::PokerCard>& cards)
{
    unsigned seed   = std::chrono::system_clock::now().time_since_epoch().count();
    auto     engine = std::default_random_engine { seed };

    std::shuffle(cards.begin(), cards.end(), engine);
}

template<typename T>
void th::Random::shuffle(std::vector<T>& elements)
{
    unsigned seed   = std::chrono::system_clock::now().time_since_epoch().count();
    auto     engine = std::default_random_engine { seed };

    std::shuffle(elements.begin(), elements.end(), engine);
}
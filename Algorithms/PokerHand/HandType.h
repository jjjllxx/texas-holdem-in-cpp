#pragma once

#include <unordered_map>
#include <vector>

namespace th
{
struct PokerCard;

enum class PokerHandType
{
    INVALID,

    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullOfHouse,
    FourOfAKind,
    StraightFlush
};

namespace HandType
{
    th::PokerHandType deduceHandType(const std::vector<th::PokerCard>& oneHand);

    bool isFlush(const std::vector<th::PokerCard>& oneHand);
    bool isStraight(const std::vector<th::PokerCard>& oneHand);
    bool isFourOfAKind(const std::unordered_map<int32_t, int32_t>& pointMap);
    bool isThreeOfKind(const std::unordered_map<int32_t, int32_t>& pointMap);
} // namespace HandType
} // namespace th
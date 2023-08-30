#pragma once

#include <unordered_map>
#include <vector>

namespace th
{
struct PokerCard;

enum class CardComboType
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

namespace CardType
{
    th::CardComboType deduceCardComboType(const std::vector<th::PokerCard>& fiveCards);

    bool isFlush(const std::vector<th::PokerCard>& fiveCards);
    bool isStraight(const std::vector<th::PokerCard>& fiveCards);
    bool isFourOfAKind(const std::unordered_map<int32_t, int32_t>& pointCount);
    bool isThreeOfKind(const std::unordered_map<int32_t, int32_t>& pointCount);
} // namespace CardType
} // namespace th
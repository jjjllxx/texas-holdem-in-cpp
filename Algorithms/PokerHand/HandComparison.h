#pragma once

#include <vector>

namespace th
{
struct PokerCard;
enum class PokerHandType;

enum class HandCmpResult
{
    INVALID,

    Win,
    Lose,
    Draw
};

namespace HandComparison
{
    th::HandCmpResult compareHand(const std::vector<th::PokerCard>& firstCards,
                                  const std::vector<th::PokerCard>& secondCards);

    std::vector<th::PokerCard> deduceCardCmpOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> deduceCardCmpOrder(const th::PokerHandType           comboType,
                                                  const std::vector<th::PokerCard>& fiveCards);

    std::vector<th::PokerCard> sortCardsByPoint(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> deduceOnePairOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> deduceTwoPairsOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> deduceThreeOfAKindOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> deduceStraightOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> deduceFullOfHouseOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> deduceFourOfAKindOrder(const std::vector<th::PokerCard>& fiveCards);

} // namespace HandComparison
} // namespace th
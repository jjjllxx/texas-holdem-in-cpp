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
    th::HandCmpResult compareHand(const std::vector<th::PokerCard>& firstHand,
                                  const std::vector<th::PokerCard>& secondHand);

    std::vector<th::PokerCard> deduceHandCmpOrder(const std::vector<th::PokerCard>& oneHand);
    std::vector<th::PokerCard> deduceHandCmpOrder(const th::PokerHandType           handType,
                                                  const std::vector<th::PokerCard>& oneHand);

    std::vector<th::PokerCard> sortHandByPoint(const std::vector<th::PokerCard>& oneHand);
    std::vector<th::PokerCard> deduceOnePairOrder(const std::vector<th::PokerCard>& oneHand);
    std::vector<th::PokerCard> deduceTwoPairsOrder(const std::vector<th::PokerCard>& oneHand);
    std::vector<th::PokerCard> deduceThreeOfAKindOrder(const std::vector<th::PokerCard>& oneHand);
    std::vector<th::PokerCard> deduceStraightOrder(const std::vector<th::PokerCard>& oneHand);
    std::vector<th::PokerCard> deduceFullOfHouseOrder(const std::vector<th::PokerCard>& oneHand);
    std::vector<th::PokerCard> deduceFourOfAKindOrder(const std::vector<th::PokerCard>& oneHand);

} // namespace HandComparison
} // namespace th
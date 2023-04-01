#pragma once

#include <vector>

namespace th
{
struct PokerCard;
enum class CardComboType;

enum class ComparisonResult
{
    INVALID,

    Win,
    Lose,
    Draw
};

namespace CardComparison
{
    th::ComparisonResult compareCardCombo(const std::vector<th::PokerCard>& firstCards,
                                          const std::vector<th::PokerCard>& secondCards);

    std::vector<th::PokerCard> generateCardCombo(const th::CardComboType           comboType,
                                                 const std::vector<th::PokerCard>& fiveCards);

    std::vector<th::PokerCard> calcHighCardOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> calcOnePairOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> calcTwoPairsOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> calcThreeOfAKindOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> calcStraightOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> calcFlushOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> calcFullOfHouseOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> calcFourOfAKindOrder(const std::vector<th::PokerCard>& fiveCards);
    std::vector<th::PokerCard> calcStraightFlushOrder(const std::vector<th::PokerCard>& fiveCards);

} // namespace CardComparison
} // namespace th
#include <unordered_map>
#include "CardType.h"


th::CardComboType th::CardTypeUtility::judgeCardCombo(const std::vector<th::PokerCard>& fiveCards)
{
    if (fiveCards.size() != 5)
    {
        return th::CardComboType::INVALID;
    }

    const bool isFlush = th::CardTypeUtility::isFlush(fiveCards);
    const bool isStraight = th::CardTypeUtility::isStraight(fiveCards);


    if (isFlush == true && isStraight == true)
    {
        return th::CardComboType::StraightFlush;
    }

    if (isFlush == true)
    {
        return th::CardComboType::Flush;
    }

    if (isStraight == true)
    {
        return th::CardComboType::Straight;
    }

    std::unordered_map<int32_t, int32_t> pointCount;
    for (const th::PokerCard& card : fiveCards)
    {
        pointCount[card.point]++;
    }

    switch (pointCount.size())
    {
        case 5:
            return th::CardComboType::HighCard;
        case 4:
            return th::CardComboType::OnePair;
        case 3:
            return th::CardTypeUtility::isThreeOfKind(pointCount) == true
                   ? th::CardComboType::ThreeOfAKind
                   : th::CardComboType::TwoPairs;
        case 2:
            return th::CardTypeUtility::isFourOfAKind(pointCount) == true
            ? th::CardComboType::FourOfAKind
            : th::CardComboType::FullOfHouse;
        default:
            break;
    }
    return th::CardComboType::INVALID;
}

bool th::CardTypeUtility::isFlush(const std::vector<th::PokerCard>& fiveCards)
{
    for (std::size_t i = 1; i < 5; ++i)
    {
        if (fiveCards[i].suit != fiveCards[i - 1].suit)
        {
            return false;
        }
    }

    return true;
}

bool th::CardTypeUtility::isStraight(const std::vector<th::PokerCard>& fiveCards)
{
    auto sortByPoint = [](const th::PokerCard& card1, const th::PokerCard& card2){return card1.point < card2.point;};
    std::sort(fiveCards.begin(), fiveCards.end(), sortByPoint);

    // A, 5, 4, 3, 2
    if (fiveCards[0].point == 14
    && fiveCards[1].point == 5
    && fiveCards[2].point == 4
    && fiveCards[3].point == 3
    && fiveCards[4].point == 2)
    {
        return true;
    }

    for (std::size_t i = 1; i < 5; ++i)
    {
        if(fiveCards[i].point - fiveCards[i - 1].point != 1)
        {
            return false;
        }
    }

    return true;
}

bool th::CardTypeUtility::isFourOfAKind(const std::unordered_map<int32_t, int32_t>& pointCount)
{
    return std::any_of(pointCount.begin(), pointCount.end(), [](const auto& p){return p.second == 4;});
}

bool th::CardTypeUtility::isThreeOfKind(const std::unordered_map<int32_t, int32_t>& pointCount)
{
    return std::any_of(pointCount.begin(), pointCount.end(), [](const auto& p){return p.second == 3;});
}


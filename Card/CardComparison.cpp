#include "CardComparison.h"

#include "CardType.h"
#include "PokerCard.h"

th::ComparisonResult th::CardComparison::compareCardCombo(const std::vector<th::PokerCard>& firstCards,
                                                          const std::vector<th::PokerCard>& secondCards)
{
    const th::CardComboType firstType  = th::CardType::calcCardComboType(firstCards);
    const th::CardComboType secondType = th::CardType::calcCardComboType(secondCards);

    if (firstType == th::CardComboType::INVALID || secondType == th::CardComboType::INVALID)
    {
        return th::ComparisonResult::INVALID;
    }

    if (firstType > secondType)
    {
        return th::ComparisonResult::Win;
    }

    if (firstType < secondType)
    {
        return th::ComparisonResult::Lose;
    }

    const std::vector<th::PokerCard> firstCmpOrder  = th::CardComparison::generateCardCombo(firstType, firstCards);
    const std::vector<th::PokerCard> secondCmpOrder = th::CardComparison::generateCardCombo(secondType, secondCards);

    for (std::size_t i = 0; i < 5; ++i)
    {
        if (firstCmpOrder[i].point > secondCmpOrder[i].point)
        {
            return th::ComparisonResult::Win;
        }

        if (firstCmpOrder[i].point < secondCmpOrder[i].point)
        {
            return th::ComparisonResult::Lose;
        }
    }

    return th::ComparisonResult::Draw;
}

std::vector<th::PokerCard> th::CardComparison::generateCardCombo(const th::CardComboType           comboType,
                                                                 const std::vector<th::PokerCard>& fiveCards)
{
    switch (comboType)
    {
    case th::CardComboType::HighCard:
        return th::CardComparison::calcHighCardOrder(fiveCards);

    case th::CardComboType::OnePair:
        return th::CardComparison::calcOnePairOrder(fiveCards);

    case th::CardComboType::TwoPairs:
        return th::CardComparison::calcTwoPairsOrder(fiveCards);

    case th::CardComboType::ThreeOfAKind:
        return th::CardComparison::calcThreeOfAKindOrder(fiveCards);

    case th::CardComboType::Straight:
        return th::CardComparison::calcStraightOrder(fiveCards);

    case th::CardComboType::Flush:
        return th::CardComparison::calcFlushOrder(fiveCards);

    case th::CardComboType::FullOfHouse:
        return th::CardComparison::calcFullOfHouseOrder(fiveCards);

    case th::CardComboType::FourOfAKind:
        return th::CardComparison::calcFourOfAKindOrder(fiveCards);

    case th::CardComboType::StraightFlush:
        return th::CardComparison::calcStraightFlushOrder(fiveCards);

    case th::CardComboType::INVALID:
    default:
        return {};
    }
}

std::vector<th::PokerCard> th::CardComparison::calcHighCardOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder;
    cmpOrder.reserve(5);

    for (const th::PokerCard& card : fiveCards)
    {
        cmpOrder.push_back(card);
    }

    std::sort(cmpOrder.begin(), cmpOrder.end(), [](const th::PokerCard& a, const th::PokerCard& b)
              {
                  return a.point > b.point;
              });

    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::calcOnePairOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::calcHighCardOrder(fiveCards);

    if (cmpOrder[3].point == cmpOrder[4].point) // 5, 4, 3, 2, 2
    {
        std::swap(cmpOrder[0], cmpOrder[4]); // 2, 4, 3, 2, 5
        std::swap(cmpOrder[1], cmpOrder[3]); // 2, 2, 3, 4, 5
        std::swap(cmpOrder[2], cmpOrder[4]); // 2, 2, 5, 4, 3
    }

    if (cmpOrder[2].point == cmpOrder[3].point) // 5, 4, 3, 3, 2
    {
        std::swap(cmpOrder[0], cmpOrder[2]); // 3, 4, 5, 3, 2
        std::swap(cmpOrder[1], cmpOrder[3]); // 3, 3, 5, 4, 2
    }

    if (cmpOrder[1].point == cmpOrder[2].point) // 5, 4, 4, 3, 2
    {
        std::swap(cmpOrder[0], cmpOrder[2]); // 4, 4, 5, 3, 2
    }

    // 5, 5, 4, 3, 2
    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::calcTwoPairsOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::calcHighCardOrder(fiveCards);

    if (cmpOrder[0].point != cmpOrder[1].point) // 5, 3, 3, 2, 2
    {
        std::swap(cmpOrder[0], cmpOrder[4]); // 2, 3, 3, 2, 5
        std::swap(cmpOrder[0], cmpOrder[2]); // 3, 3, 2, 2, 5
    }

    if (cmpOrder[2].point != cmpOrder[3].point) // 5, 5, 3, 2, 2
    {
        std::swap(cmpOrder[2], cmpOrder[5]); // 5, 5, 2, 2, 3
    }

    // 5, 5, 3, 3, 2
    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::calcThreeOfAKindOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::calcHighCardOrder(fiveCards);

    if (cmpOrder[0].point != cmpOrder[1].point) // 5, 3, 3, 3, 2
    {
        std::swap(cmpOrder[0], cmpOrder[3]); // 3, 3, 3, 5, 2
    }

    if (cmpOrder[1].point != cmpOrder[2].point) // 5, 3, 2, 2, 2 -> 2, 3, 2, 5, 2 (Already done in the first if)
    {
        std::swap(cmpOrder[1], cmpOrder[4]); // 2, 2, 2, 5, 3
    }

    // 5, 5, 5, 3, 2
    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::calcStraightOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::calcHighCardOrder(fiveCards);

    // For A, 2, 3, 4, 5 staright, it will be sorted as A, 5, 4, 3, 2. Move A to the back.
    if (cmpOrder.front().point == 14 && cmpOrder[1].point != 13)
    {
        cmpOrder.push_back(cmpOrder.front()); // A, 5, 4, 3, 2, A
        cmpOrder.erase(cmpOrder.begin());     // 5, 4, 3, 2, A
    }

    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::calcFlushOrder(const std::vector<th::PokerCard>& fiveCards)
{
    return th::CardComparison::calcHighCardOrder(fiveCards);
}

std::vector<th::PokerCard> th::CardComparison::calcFullOfHouseOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::calcHighCardOrder(fiveCards);

    if (cmpOrder[2].point != cmpOrder[1].point) // 2, 2, 3, 3, 3
    {
        std::swap(cmpOrder[0], cmpOrder[4]); // 3, 2, 3, 3, 2
        std::swap(cmpOrder[1], cmpOrder[3]); // 3, 3, 3, 2, 2
    }

    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::calcFourOfAKindOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::calcHighCardOrder(fiveCards);

    if (cmpOrder[0].point != cmpOrder[1].point) // 3, 2, 2, 2, 2
    {
        std::swap(cmpOrder.front(), cmpOrder.back()); // 2, 2, 2, 2, 3
    }

    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::calcStraightFlushOrder(const std::vector<th::PokerCard>& fiveCards)
{
    return th::CardComparison::calcStraightOrder(fiveCards);
}
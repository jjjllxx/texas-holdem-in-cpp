#include "CardComparison.h"

#include "Entity/Card/PokerCard.h"

#include "CardType.h"
#include "Utilities/Constants.h"

th::CardComboCmpResult th::CardComparison::compareCardCombo(const std::vector<th::PokerCard>& firstCards,
                                                            const std::vector<th::PokerCard>& secondCards)
{
    const th::CardComboType firstType  = th::CardType::deduceCardComboType(firstCards);
    const th::CardComboType secondType = th::CardType::deduceCardComboType(secondCards);

    if (firstType == th::CardComboType::INVALID || secondType == th::CardComboType::INVALID)
    {
        return th::CardComboCmpResult::INVALID;
    }

    if (firstType > secondType)
    {
        return th::CardComboCmpResult::Win;
    }

    if (firstType < secondType)
    {
        return th::CardComboCmpResult::Lose;
    }

    const std::vector<th::PokerCard> firstCmpOrder  = th::CardComparison::deduceCardCmpOrder(firstType, firstCards);
    const std::vector<th::PokerCard> secondCmpOrder = th::CardComparison::deduceCardCmpOrder(secondType, secondCards);

    for (std::size_t i = 0; i < th::STANDARD_CARD_COMBO_SIZE; ++i)
    {
        if (firstCmpOrder[i].point > secondCmpOrder[i].point)
        {
            return th::CardComboCmpResult::Win;
        }

        if (firstCmpOrder[i].point < secondCmpOrder[i].point)
        {
            return th::CardComboCmpResult::Lose;
        }
    }

    return th::CardComboCmpResult::Draw;
}

std::vector<th::PokerCard> th::CardComparison::deduceCardCmpOrder(const th::CardComboType           comboType,
                                                                  const std::vector<th::PokerCard>& fiveCards)
{
    switch (comboType)
    {
    case th::CardComboType::Flush:
    case th::CardComboType::HighCard:
        return th::CardComparison::sortCardsByPoint(fiveCards);

    case th::CardComboType::OnePair:
        return th::CardComparison::deduceOnePairOrder(fiveCards);

    case th::CardComboType::TwoPairs:
        return th::CardComparison::deduceTwoPairsOrder(fiveCards);

    case th::CardComboType::ThreeOfAKind:
        return th::CardComparison::deduceThreeOfAKindOrder(fiveCards);

    case th::CardComboType::Straight:
    case th::CardComboType::StraightFlush:
        return th::CardComparison::deduceStraightOrder(fiveCards);

    case th::CardComboType::FullOfHouse:
        return th::CardComparison::deduceFullOfHouseOrder(fiveCards);

    case th::CardComboType::FourOfAKind:
        return th::CardComparison::deduceFourOfAKindOrder(fiveCards);

    case th::CardComboType::INVALID:
    default:
        return {};
    }
}

std::vector<th::PokerCard> th::CardComparison::sortCardsByPoint(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder;
    cmpOrder.reserve(th::STANDARD_CARD_COMBO_SIZE);

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

std::vector<th::PokerCard> th::CardComparison::deduceOnePairOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::sortCardsByPoint(fiveCards);

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

std::vector<th::PokerCard> th::CardComparison::deduceTwoPairsOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::sortCardsByPoint(fiveCards);

    if (cmpOrder[0].point != cmpOrder[1].point) // 5, 3, 3, 2, 2
    {
        std::swap(cmpOrder[0], cmpOrder[4]); // 2, 3, 3, 2, 5
        std::swap(cmpOrder[0], cmpOrder[2]); // 3, 3, 2, 2, 5
    }

    if (cmpOrder[2].point != cmpOrder[3].point) // 5, 5, 3, 2, 2
    {
        std::swap(cmpOrder[2], cmpOrder[4]); // 5, 5, 2, 2, 3
    }

    // 5, 5, 3, 3, 2
    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::deduceThreeOfAKindOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::sortCardsByPoint(fiveCards);

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

std::vector<th::PokerCard> th::CardComparison::deduceStraightOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::sortCardsByPoint(fiveCards);

    // For A, 2, 3, 4, 5 staright, it will be sorted as A, 5, 4, 3, 2. Move A to the back.
    if (cmpOrder.front().point == 14 && cmpOrder[1].point != 13)
    {
        cmpOrder.push_back(cmpOrder.front()); // A, 5, 4, 3, 2, A
        cmpOrder.erase(cmpOrder.begin());     // 5, 4, 3, 2, A
    }

    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::deduceFullOfHouseOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::sortCardsByPoint(fiveCards);

    if (cmpOrder[2].point != cmpOrder[1].point) // 2, 2, 3, 3, 3
    {
        std::swap(cmpOrder[0], cmpOrder[4]); // 3, 2, 3, 3, 2
        std::swap(cmpOrder[1], cmpOrder[3]); // 3, 3, 3, 2, 2
    }

    return cmpOrder;
}

std::vector<th::PokerCard> th::CardComparison::deduceFourOfAKindOrder(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<th::PokerCard> cmpOrder = th::CardComparison::sortCardsByPoint(fiveCards);

    if (cmpOrder[0].point != cmpOrder[1].point) // 3, 2, 2, 2, 2
    {
        std::swap(cmpOrder.front(), cmpOrder.back()); // 2, 2, 2, 2, 3
    }

    return cmpOrder;
}
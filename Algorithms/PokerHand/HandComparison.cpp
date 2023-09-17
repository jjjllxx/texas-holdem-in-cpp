#include "HandComparison.h"

#include "Entity/Card/PokerCard.h"

#include "HandType.h"
#include "Utilities/Constants.h"

#include <algorithm>

th::HandCmpResult th::HandComparison::compareHand(const std::vector<th::PokerCard>& firstHand,
                                                  const std::vector<th::PokerCard>& secondHand)
{
    const th::PokerHandType firstType  = th::HandType::deduceHandType(firstHand);
    const th::PokerHandType secondType = th::HandType::deduceHandType(secondHand);

    if (firstType == th::PokerHandType::INVALID || secondType == th::PokerHandType::INVALID)
    {
        return th::HandCmpResult::INVALID;
    }

    if (firstType > secondType)
    {
        return th::HandCmpResult::Win;
    }

    if (firstType < secondType)
    {
        return th::HandCmpResult::Lose;
    }

    const std::vector<th::PokerCard> firstCmpOrder  = th::HandComparison::deduceHandCmpOrder(firstType, firstHand);
    const std::vector<th::PokerCard> secondCmpOrder = th::HandComparison::deduceHandCmpOrder(secondType, secondHand);

    for (std::size_t i = 0; i < th::STANDARD_HAND_SIZE; ++i)
    {
        if (firstCmpOrder[i].point > secondCmpOrder[i].point)
        {
            return th::HandCmpResult::Win;
        }

        if (firstCmpOrder[i].point < secondCmpOrder[i].point)
        {
            return th::HandCmpResult::Lose;
        }
    }

    return th::HandCmpResult::Draw;
}

std::vector<th::PokerCard> th::HandComparison::deduceHandCmpOrder(const std::vector<th::PokerCard>& oneHand)
{
    const th::PokerHandType handType = th::HandType::deduceHandType(oneHand);

    return th::HandComparison::deduceHandCmpOrder(handType, oneHand);
}

std::vector<th::PokerCard> th::HandComparison::deduceHandCmpOrder(const th::PokerHandType           handType,
                                                                  const std::vector<th::PokerCard>& oneHand)
{
    switch (handType)
    {
    case th::PokerHandType::Flush:
    case th::PokerHandType::HighCard:
        return th::HandComparison::sortHandByPoint(oneHand);

    case th::PokerHandType::OnePair:
        return th::HandComparison::deduceOnePairOrder(oneHand);

    case th::PokerHandType::TwoPairs:
        return th::HandComparison::deduceTwoPairsOrder(oneHand);

    case th::PokerHandType::ThreeOfAKind:
        return th::HandComparison::deduceThreeOfAKindOrder(oneHand);

    case th::PokerHandType::Straight:
    case th::PokerHandType::StraightFlush:
        return th::HandComparison::deduceStraightOrder(oneHand);

    case th::PokerHandType::FullOfHouse:
        return th::HandComparison::deduceFullOfHouseOrder(oneHand);

    case th::PokerHandType::FourOfAKind:
        return th::HandComparison::deduceFourOfAKindOrder(oneHand);

    case th::PokerHandType::INVALID:
    default:
        return oneHand;
    }
}

std::vector<th::PokerCard> th::HandComparison::sortHandByPoint(const std::vector<th::PokerCard>& oneHand)
{
    std::vector<th::PokerCard> cmpOrder;
    cmpOrder.reserve(th::STANDARD_HAND_SIZE);

    for (const th::PokerCard& card : oneHand)
    {
        cmpOrder.push_back(card);
    }

    std::sort(cmpOrder.begin(), cmpOrder.end(), [](const th::PokerCard& a, const th::PokerCard& b)
              {
                  return a.point > b.point;
              });

    return cmpOrder;
}

std::vector<th::PokerCard> th::HandComparison::deduceOnePairOrder(const std::vector<th::PokerCard>& oneHand)
{
    std::vector<th::PokerCard> cmpOrder = th::HandComparison::sortHandByPoint(oneHand);

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

std::vector<th::PokerCard> th::HandComparison::deduceTwoPairsOrder(const std::vector<th::PokerCard>& oneHand)
{
    std::vector<th::PokerCard> cmpOrder = th::HandComparison::sortHandByPoint(oneHand);

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

std::vector<th::PokerCard> th::HandComparison::deduceThreeOfAKindOrder(const std::vector<th::PokerCard>& oneHand)
{
    std::vector<th::PokerCard> cmpOrder = th::HandComparison::sortHandByPoint(oneHand);

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

std::vector<th::PokerCard> th::HandComparison::deduceStraightOrder(const std::vector<th::PokerCard>& oneHand)
{
    std::vector<th::PokerCard> cmpOrder = th::HandComparison::sortHandByPoint(oneHand);

    // For A, 2, 3, 4, 5 staright, it will be sorted as A, 5, 4, 3, 2. Move A to the back.
    if (cmpOrder.front().point == 14 && cmpOrder[1].point != 13)
    {
        cmpOrder.push_back(cmpOrder.front()); // A, 5, 4, 3, 2, A
        cmpOrder.erase(cmpOrder.begin());     // 5, 4, 3, 2, A
    }

    return cmpOrder;
}

std::vector<th::PokerCard> th::HandComparison::deduceFullOfHouseOrder(const std::vector<th::PokerCard>& oneHand)
{
    std::vector<th::PokerCard> cmpOrder = th::HandComparison::sortHandByPoint(oneHand);

    if (cmpOrder[2].point != cmpOrder[1].point) // 2, 2, 3, 3, 3
    {
        std::swap(cmpOrder[0], cmpOrder[4]); // 3, 2, 3, 3, 2
        std::swap(cmpOrder[1], cmpOrder[3]); // 3, 3, 3, 2, 2
    }

    return cmpOrder;
}

std::vector<th::PokerCard> th::HandComparison::deduceFourOfAKindOrder(const std::vector<th::PokerCard>& oneHand)
{
    std::vector<th::PokerCard> cmpOrder = th::HandComparison::sortHandByPoint(oneHand);

    if (cmpOrder[0].point != cmpOrder[1].point) // 3, 2, 2, 2, 2
    {
        std::swap(cmpOrder.front(), cmpOrder.back()); // 2, 2, 2, 2, 3
    }

    return cmpOrder;
}
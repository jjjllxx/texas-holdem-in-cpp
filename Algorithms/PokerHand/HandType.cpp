#include "HandType.h"

#include "Entity/Card/PokerCard.h"
#include "Utilities/Constants.h"

#include <algorithm>

th::PokerHandType th::HandType::deduceHandType(const std::vector<th::PokerCard>& oneHand)
{
    if (oneHand.size() != th::STANDARD_HAND_SIZE)
    {
        return th::PokerHandType::INVALID;
    }

    const bool isFlush    = th::HandType::isFlush(oneHand);
    const bool isStraight = th::HandType::isStraight(oneHand);

    if (isFlush == true && isStraight == true)
    {
        return th::PokerHandType::StraightFlush;
    }

    if (isFlush == true)
    {
        return th::PokerHandType::Flush;
    }

    if (isStraight == true)
    {
        return th::PokerHandType::Straight;
    }

    std::unordered_map<int32_t, int32_t> pointMap;
    for (const th::PokerCard& card : oneHand)
    {
        pointMap[card.point]++;
    }

    switch (pointMap.size())
    {
    case 5:
        return th::PokerHandType::HighCard;
    case 4:
        return th::PokerHandType::OnePair;
    case 3:
        return th::HandType::isThreeOfKind(pointMap) == true
                   ? th::PokerHandType::ThreeOfAKind
                   : th::PokerHandType::TwoPairs;
    case 2:
        return th::HandType::isFourOfAKind(pointMap) == true
                   ? th::PokerHandType::FourOfAKind
                   : th::PokerHandType::FullOfHouse;
    default:
        break;
    }

    return th::PokerHandType::INVALID;
}

bool th::HandType::isFlush(const std::vector<th::PokerCard>& oneHand)
{
    for (std::size_t i = 1; i < th::STANDARD_HAND_SIZE; ++i)
    {
        if (oneHand[i].suit != oneHand[i - 1].suit)
        {
            return false;
        }
    }

    return true;
}

bool th::HandType::isStraight(const std::vector<th::PokerCard>& oneHand)
{
    std::vector<int32_t> cardPts;
    cardPts.reserve(oneHand.size());

    for (const th::PokerCard& card : oneHand)
    {
        cardPts.push_back(card.point);
    }

    std::sort(cardPts.begin(), cardPts.end());

    // A, 5, 4, 3, 2
    if (cardPts[0] == 2 && cardPts[1] == 3 && cardPts[2] == 4 && cardPts[3] == 5 && cardPts[4] == 14)
    {
        return true;
    }

    for (std::size_t i = 1; i < th::STANDARD_HAND_SIZE; ++i)
    {
        if (cardPts[i] - cardPts[i - 1] != 1)
        {
            return false;
        }
    }

    return true;
}

bool th::HandType::isFourOfAKind(const std::unordered_map<int32_t, int32_t>& pointMap)
{
    return std::any_of(pointMap.begin(), pointMap.end(), [](const auto& p)
                       {
                           return p.second == 4;
                       });
}

bool th::HandType::isThreeOfKind(const std::unordered_map<int32_t, int32_t>& pointMap)
{
    return std::any_of(pointMap.begin(), pointMap.end(), [](const auto& p)
                       {
                           return p.second == 3;
                       });
}
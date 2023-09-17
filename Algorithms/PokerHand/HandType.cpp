#include "HandType.h"

#include "Entity/Card/PokerCard.h"
#include "Utilities/Constants.h"

#include <algorithm>

th::PokerHandType th::HandType::deduceHandType(const std::vector<th::PokerCard>& fiveCards)
{
    if (fiveCards.size() != th::STANDARD_CARD_COMBO_SIZE)
    {
        return th::PokerHandType::INVALID;
    }

    const bool isFlush    = th::HandType::isFlush(fiveCards);
    const bool isStraight = th::HandType::isStraight(fiveCards);

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

    std::unordered_map<int32_t, int32_t> pointCount;
    for (const th::PokerCard& card : fiveCards)
    {
        pointCount[card.point]++;
    }

    switch (pointCount.size())
    {
    case 5:
        return th::PokerHandType::HighCard;
    case 4:
        return th::PokerHandType::OnePair;
    case 3:
        return th::HandType::isThreeOfKind(pointCount) == true
                   ? th::PokerHandType::ThreeOfAKind
                   : th::PokerHandType::TwoPairs;
    case 2:
        return th::HandType::isFourOfAKind(pointCount) == true
                   ? th::PokerHandType::FourOfAKind
                   : th::PokerHandType::FullOfHouse;
    default:
        break;
    }

    return th::PokerHandType::INVALID;
}

bool th::HandType::isFlush(const std::vector<th::PokerCard>& fiveCards)
{
    for (std::size_t i = 1; i < th::STANDARD_CARD_COMBO_SIZE; ++i)
    {
        if (fiveCards[i].suit != fiveCards[i - 1].suit)
        {
            return false;
        }
    }

    return true;
}

bool th::HandType::isStraight(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<int32_t> cardPts;
    cardPts.reserve(fiveCards.size());

    for (const th::PokerCard& card : fiveCards)
    {
        cardPts.push_back(card.point);
    }

    std::sort(cardPts.begin(), cardPts.end());

    // A, 5, 4, 3, 2
    if (cardPts[0] == 2 && cardPts[1] == 3 && cardPts[2] == 4 && cardPts[3] == 5 && cardPts[4] == 14)
    {
        return true;
    }

    for (std::size_t i = 1; i < th::STANDARD_CARD_COMBO_SIZE; ++i)
    {
        if (cardPts[i] - cardPts[i - 1] != 1)
        {
            return false;
        }
    }

    return true;
}

bool th::HandType::isFourOfAKind(const std::unordered_map<int32_t, int32_t>& pointCount)
{
    return std::any_of(pointCount.begin(), pointCount.end(), [](const auto& p)
                       {
                           return p.second == 4;
                       });
}

bool th::HandType::isThreeOfKind(const std::unordered_map<int32_t, int32_t>& pointCount)
{
    return std::any_of(pointCount.begin(), pointCount.end(), [](const auto& p)
                       {
                           return p.second == 3;
                       });
}
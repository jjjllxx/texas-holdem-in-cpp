#include "CardType.h"

#include "../../Entity/Card/PokerCard.h"

th::CardComboType th::CardType::calcCardComboType(const std::vector<th::PokerCard>& fiveCards)
{
    if (fiveCards.size() != 5)
    {
        return th::CardComboType::INVALID;
    }

    const bool isFlush    = th::CardType::isFlush(fiveCards);
    const bool isStraight = th::CardType::isStraight(fiveCards);

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
        return th::CardType::isThreeOfKind(pointCount) == true
                   ? th::CardComboType::ThreeOfAKind
                   : th::CardComboType::TwoPairs;
    case 2:
        return th::CardType::isFourOfAKind(pointCount) == true
                   ? th::CardComboType::FourOfAKind
                   : th::CardComboType::FullOfHouse;
    default:
        break;
    }

    return th::CardComboType::INVALID;
}

bool th::CardType::isFlush(const std::vector<th::PokerCard>& fiveCards)
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

bool th::CardType::isStraight(const std::vector<th::PokerCard>& fiveCards)
{
    std::vector<int32_t> cardPts;
    cardPts.reserve(fiveCards.size());

    for (const th::PokerCard& card : fiveCards)
    {
        cardPts.push_back(card.point);
    }

    std::sort(cardPts.begin(), cardPts.end());

    // A, 5, 4, 3, 2
    if (cardPts[0] == 14 && cardPts[1] == 5 && cardPts[2] == 4 && cardPts[3] == 3 && cardPts[4] == 2)
    {
        return true;
    }

    for (std::size_t i = 1; i < 5; ++i)
    {
        if (cardPts[i] - cardPts[i - 1] != 1)
        {
            return false;
        }
    }

    return true;
}

bool th::CardType::isFourOfAKind(const std::unordered_map<int32_t, int32_t>& pointCount)
{
    return std::any_of(pointCount.begin(), pointCount.end(), [](const auto& p)
                       {
                           return p.second == 4;
                       });
}

bool th::CardType::isThreeOfKind(const std::unordered_map<int32_t, int32_t>& pointCount)
{
    return std::any_of(pointCount.begin(), pointCount.end(), [](const auto& p)
                       {
                           return p.second == 3;
                       });
}
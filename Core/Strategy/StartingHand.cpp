#include "StartingHand.h"

#include "Entity/Card/PokerCard.h"
#include "Entity/Score/Score.h"

#include <algorithm>

th::score th::StartingHand::calcScore(const th::PokerCard& firstCard,
                                      const th::PokerCard& secondCard)
{
    // For more details of this method, refer to Chen formula
    // in https://en.wikipedia.org/wiki/Texas_hold_%27em_starting_hands#Chen_formula
    // Small variant: Take double of highest card score to avoid decimal

    const th::score highestCardScore = firstCard.point > secondCard.point
                                           ? th::StartingHand::calcHighestCardScore(firstCard)
                                           : th::StartingHand::calcHighestCardScore(secondCard);

    if (th::StartingHand::isPair(firstCard, secondCard))
    {
        return th::StartingHand::calcPairScore(highestCardScore);
    }

    const th::score gappersDeduction = th::StartingHand::calcGappersDeduction(firstCard, secondCard);
    const th::score suitedScore      = th::StartingHand::isSuited(firstCard, secondCard) == true
                                           ? 4
                                           : 0;

    return highestCardScore - gappersDeduction + suitedScore;
}

th::score th::StartingHand::calcHighestCardScore(const th::PokerCard& highestCard)
{
    switch (highestCard.point)
    {
    case 14:
        return 20;
    case 13:
    case 12:
    case 11:
        return (highestCard.point - 5) * 2;
    default:
        return highestCard.point;
    }
}

th::score th::StartingHand::calcPairScore(const th::score& highestCardScore)
{
    if (highestCardScore == 5)
    {
        return 12;
    }

    if (highestCardScore < 5)
    {
        return 10;
    }

    return highestCardScore * 2;
}

th::score th::StartingHand::calcGappersDeduction(const th::PokerCard& firstCard,
                                                 const th::PokerCard& secondCard)
{
    const int  gappersCnt              = std::abs(firstCard.point - secondCard.point) - 1;
    const bool isHighestCardLowerThanQ = std::max(firstCard.point, secondCard.point) < 12;

    const th::score extraScore = isHighestCardLowerThanQ == true ? 2 : 0;

    switch (gappersCnt)
    {
    case 0:
    case 1:
        return th::score(gappersCnt << 1) - extraScore;
    case 2:
        return gappersCnt << 1;
    case 3:
        return 8;
    default:
        return 10;
    }
}

bool th::StartingHand::isSuited(const th::PokerCard& firstCard,
                                const th::PokerCard& secondCard)
{
    return firstCard.suit == secondCard.suit;
}

bool th::StartingHand::isPair(const th::PokerCard& firstCard,
                              const th::PokerCard& secondCard)
{
    return firstCard.point == secondCard.point;
}

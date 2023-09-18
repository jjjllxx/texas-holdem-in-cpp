#pragma once

namespace th
{
struct score;
struct PokerCard;

namespace StartingHand
{
    th::score calcScore(const th::PokerCard& firstCard,
                        const th::PokerCard& secondCard);
    th::score calcPairScore(const th::score& highestCardScore);
    th::score calcHighestCardScore(const th::PokerCard& highestCard);
    th::score calcGappersDeduction(const th::PokerCard& firstCard,
                                   const th::PokerCard& secondCard);

    bool isSuited(const th::PokerCard& firstCard,
                  const th::PokerCard& secondCard);
    bool isPair(const th::PokerCard& firstCard,
                const th::PokerCard& secondCard);

} // namespace StartingHand
} // namespace th
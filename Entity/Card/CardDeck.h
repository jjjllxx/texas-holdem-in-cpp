#pragma once

#include "PokerCard.h"

#include <vector>

namespace th
{
struct CardDeck
{
    CardDeck();

    void init();
    void shuffle();

    th::PokerCard getCurrTop();
    th::PokerCard getCurrTopNext();

private:
    std::size_t                currTopCard;
    std::vector<th::PokerCard> cards;

    void initOneSuit(const th::CardSuit suit);
};
}
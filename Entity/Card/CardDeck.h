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

    th::PokerCard getCurTop();
    th::PokerCard getCurTopNext();

private:
    std::size_t                curTopCard;
    std::vector<th::PokerCard> cards;

    void initOneSuit(const th::CardSuit suit);
};
}
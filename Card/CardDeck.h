#pragma once

#include "PokerCard.h"

#include <vector>

namespace th
{
    struct CardDeck
    {
        CardDeck();

        std::size_t currTopCard;
        std::vector<th::PokerCard> cards;

        void init();
        void shuffle();

        th::PokerCard getCurrTop();
        th::PokerCard getCurrTopNext();
    };
}
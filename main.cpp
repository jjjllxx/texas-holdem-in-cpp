#pragma once

#include "Card/CardDeck.h"

int main(int argc, const char *argv[])
{
    th::CardDeck deck;
    deck.init();
    deck.shuffle();
    for (int32_t i = 0; i < 52; ++i)
    {
        deck.getCurrTop().print();
    }

    return 0;
}

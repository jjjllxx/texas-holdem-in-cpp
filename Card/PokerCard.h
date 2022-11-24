#pragma once

#include <iostream>

namespace th
{
    enum class CardSuit
    {
        INVALID,

        Club,
        Diamond,
        Heart,
        Spade,
    };

    struct PokerCard
    {
        PokerCard();
        PokerCard(const th::CardSuit suit,
                  const int32_t point);

        th::CardSuit suit;
        int32_t point;

        void print();
    };

    namespace PokerCardUtility
    {
        std::string getCardSuitStr(const th::CardSuit suit);
        std::string getCardPointStr(const int32_t point);
    }
}
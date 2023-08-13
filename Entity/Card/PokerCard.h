#pragma once

#include <string>

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
              const int32_t      point);

    th::CardSuit suit;
    int32_t      point;

    std::string getStr() const;
    std::string getSymbol() const;
};

namespace PokerCardUtility
{
    std::string getCardSuitStr(const th::CardSuit suit);
    std::string getCardSuitSymbol(const th::CardSuit suit);
    std::string getCardPointStr(const int32_t point);
} // namespace PokerCardUtility
}
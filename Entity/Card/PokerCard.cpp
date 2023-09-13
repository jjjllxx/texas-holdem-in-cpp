#include "PokerCard.h"
#include <string>

th::PokerCard::PokerCard() :
    suit(th::CardSuit::INVALID),
    point(0)
{
}

th::PokerCard::PokerCard(const th::CardSuit suit,
                         const int32_t      point) :
    suit(suit),
    point(point)
{
}

bool th::PokerCard::operator==(const th::PokerCard& card) const
{
    return card.point == this->point && card.suit == this->suit;
}

std::string th::PokerCardUtility::toSymbol(const std::vector<th::PokerCard>& cards)
{
    std::string cardsSymbol;
    for (const th::PokerCard& card : cards)
    {
        cardsSymbol += th::PokerCardUtility::toSymbol(card);
        cardsSymbol += " ";
    }

    return cardsSymbol;
}

std::string th::PokerCardUtility::toSymbol(const th::PokerCard& card)
{
    return th::PokerCardUtility::getCardSuitSymbol(card.suit)
           + th::PokerCardUtility::getCardPointStr(card.point);
}

std::string th::PokerCardUtility::getCardSuitSymbol(const th::CardSuit suit)
{
    switch (suit)
    {
    case th::CardSuit::Club:
        return "\u2663";
    case th::CardSuit::Diamond:
        return "\u2662";
    case th::CardSuit::Heart:
        return "\u2661";
    case th::CardSuit::Spade:
        return "\u2660";
    case th::CardSuit::INVALID:
    default:
        return "";
    }
}

std::string th::PokerCardUtility::getCardPointStr(const int32_t point)
{
    switch (point)
    {
    case 11:
        return "J";
    case 12:
        return "Q";
    case 13:
        return "K";
    case 14:
        return "A";
    default:
        return std::to_string(point);
    }
}
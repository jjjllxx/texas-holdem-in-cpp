#include "PokerCard.h"

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

std::string th::PokerCard::getStr() const
{
    return th::PokerCardUtility::getCardSuitStr(this->suit) + ' '
           + th::PokerCardUtility::getCardPointStr(this->point);
}

std::string th::PokerCard::getSymbol() const
{
    return th::PokerCardUtility::getCardSuitSymbol(this->suit)
           + th::PokerCardUtility::getCardPointStr(this->point);
}

std::string th::PokerCardUtility::getCardSuitStr(const th::CardSuit suit)
{
    switch (suit)
    {
    case th::CardSuit::Club:
        return "Club";
    case th::CardSuit::Diamond:
        return "Diamond";
    case th::CardSuit::Heart:
        return "Heart";
    case th::CardSuit::Spade:
        return "Spade";
    case th::CardSuit::INVALID:
    default:
        return "";
    }
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
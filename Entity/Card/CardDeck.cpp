#include "CardDeck.h"

#include "Algorithms/Random.h"
#include "Entity/Constants.h"

th::CardDeck::CardDeck() :
    curTopCard(0)
{
}

void th::CardDeck::init()
{
    this->cards.reserve(th::STANDARD_CARD_DECK_SIZE);

    th::CardDeck::initOneSuit(th::CardSuit::Club);
    th::CardDeck::initOneSuit(th::CardSuit::Diamond);
    th::CardDeck::initOneSuit(th::CardSuit::Heart);
    th::CardDeck::initOneSuit(th::CardSuit::Spade);
}

void th::CardDeck::shuffle()
{
    th::Random::shuffle(this->cards);
    this->curTopCard = 0;
}

th::PokerCard th::CardDeck::getCurTop()
{
    return this->cards[this->curTopCard++];
}

th::PokerCard th::CardDeck::getCurTopNext()
{
    this->curTopCard++;

    return th::CardDeck::getCurTop();
}

void th::CardDeck::initOneSuit(const th::CardSuit suit)
{
    for (int32_t i = 2; i < 15; ++i)
    {
        this->cards.emplace_back(suit, i);
    }
}
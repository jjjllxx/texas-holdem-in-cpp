#include <algorithm>
#include <random>

#include "CardDeck.h"

th::CardDeck::CardDeck() :
    currTopCard(0)
{
}

void th::CardDeck::init()
{
    this->cards.reserve(52);

    th::CardDeck::initOneSuit(th::CardSuit::Club);
    th::CardDeck::initOneSuit(th::CardSuit::Diamond);
    th::CardDeck::initOneSuit(th::CardSuit::Heart);
    th::CardDeck::initOneSuit(th::CardSuit::Spade);
}

void th::CardDeck::shuffle()
{
    unsigned seed         = std::chrono::system_clock::now().time_since_epoch().count();
    auto     randomEngine = std::default_random_engine { seed };
    std::shuffle(this->cards.begin(), this->cards.end(), randomEngine);

    this->currTopCard = 0;
}

th::PokerCard th::CardDeck::getCurrTop()
{
    return this->cards[this->currTopCard++];
}

th::PokerCard th::CardDeck::getCurrTopNext()
{
    this->currTopCard++;

    return th::CardDeck::getCurrTop();
}

void th::CardDeck::initOneSuit(const th::CardSuit suit)
{
    for (int32_t i = 2; i < 15; ++i)
    {
        this->cards.emplace_back(suit, i);
    }
}
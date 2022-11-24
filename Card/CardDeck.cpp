#pragma once

#include <random>
#include <algorithm>

#include "CardDeck.h"

th::CardDeck::CardDeck() : currTopCard(0)
{
}

void th::CardDeck::init()
{
    const int32_t cardNum = 52;
    this->cards.reserve(cardNum);

    for (int32_t i = 1; i < 14; ++i)
    {
        this->cards.emplace_back(th::CardSuit::Club, i);
    }

    for (int32_t i = 1; i < 14; ++i)
    {
        this->cards.emplace_back(th::CardSuit::Diamond, i);
    }

    for (int32_t i = 1; i < 14; ++i)
    {
        this->cards.emplace_back(th::CardSuit::Heart, i);
    }

    for (int32_t i = 1; i < 14; ++i)
    {
        this->cards.emplace_back(th::CardSuit::Spade, i);
    }
}

void th::CardDeck::shuffle()
{
     auto randomEngine = std::default_random_engine{};
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
#include "Game.h"

#include "../Card/CardDeck.h"
#include "../Player/BasePlayer.h"

th::Game::Game() :
    currPool(0)
{
}

bool th::Game::initGame(const std::size_t smallBlindPos,
                        const int32_t     smallBlindChip)
{
    if (smallBlindChip <= 0)
    {
        return false;
    }

    this->smallBlindPos  = smallBlindPos;
    this->smallBlindChip = smallBlindChip;

    return true;
}

void th::Game::startGame(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    players[this->smallBlindPos]->call(this->smallBlindChip);
    this->bigBlindPos = (this->smallBlindPos + 1) % players.size();
    players[this->bigBlindPos]->call(this->smallBlindChip << 1);

    this->currPool += this->smallBlindChip + (this->smallBlindChip << 1);

    th::Game::dealCards(cardDeck, players);
}

void th::Game::dealCards(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        player->receiveFirstCard(cardDeck.getCurrTop());
    }

    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        player->receiveSecondCard(cardDeck.getCurrTop());
    }
}

int32_t th::Game::getCurrPool() const
{
    return this->currPool;
}
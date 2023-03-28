#include "Game.h"

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

void th::Game::startGame(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    // Add small blind and big blind info
    players[this->smallBlindPos]->minusChip(this->smallBlindChip);
    players[(this->smallBlindPos + 1) % players.size()]->minusChip(this->smallBlindChip << 1);

    this->currPool += this->smallBlindChip + (this->smallBlindChip << 1);
}

void th::Game::endGame(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    // Remove small blind and big blind info
    (void) players;
}

int32_t th::Game::getCurrPool() const
{
    return this->currPool;
}
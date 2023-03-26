#include "GameProcess.h"

#include "../Player/AutoPlayer.h"
#include "../Player/HumanPlayer.h"

#include <iostream>

th::GameProcess::GameProcess() :
    MINIMUM_PLAYER_NUM(2),
    MAXIMUM_PLAYER_NUM(12),
    currPool(0),
    gameRound(0)
{
}

bool th::GameProcess::initPokerTable(const int32_t playerNum,
                                     const int32_t initChip)
{
    if (playerNum < this->MINIMUM_PLAYER_NUM || playerNum >= this->MAXIMUM_PLAYER_NUM)
    {
        return false;
    }

    this->players.reserve(playerNum);
    this->players.push_back(std::make_shared<th::HumanPlayer>(0));
    this->players.back()->addChip(initChip);

    for (int32_t i = 1; i < playerNum; ++i)
    {
        this->players.push_back(std::make_shared<th::AutoPlayer>(i));
        this->players.back()->addChip(initChip);
    }

    return true;
}

void th::GameProcess::clearPokerTable()
{
    this->players.clear();
}

void th::GameProcess::startANewGame()
{
    this->currPool = 0;
}

int32_t th::GameProcess::getCurrPool() const
{
    return this->currPool;
}

int32_t th::GameProcess::getGameRound() const
{
    return this->gameRound;
}
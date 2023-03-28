#include "GameTable.h"

#include "../Player/AutoPlayer.h"
#include "../Player/BasePlayer.h"
#include "../Player/HumanPlayer.h"

th::GameTable::GameTable() :
    MINIMUM_PLAYER_NUM(2),
    MAXIMUM_PLAYER_NUM(12),
    gameNum(0),
    currSmallBlindPos(0),
    currSmallBlindChip(0)
{
}

bool th::GameTable::initPokerTable(const int32_t playerNum,
                                   const int32_t initChip,
                                   const int32_t smallBlindChip)
{
    if (playerNum < this->MINIMUM_PLAYER_NUM || playerNum >= this->MAXIMUM_PLAYER_NUM)
    {
        return false;
    }

    this->currSmallBlindChip = smallBlindChip;

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

void th::GameTable::clearPokerTable()
{
    this->players.clear();
}

void th::GameTable::startANewGame()
{
    this->gameNum++;

    if (this->currGame.initGame(this->currSmallBlindPos, this->currSmallBlindChip) == true)
    {
        this->currGame.startGame(this->players);
    }
}

int32_t th::GameTable::getGameNum() const
{
    for (const auto& player : this->players)
    {
        player->showStatus();
    }

    return this->gameNum;
}
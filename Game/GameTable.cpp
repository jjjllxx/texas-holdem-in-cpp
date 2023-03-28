#include "GameTable.h"

#include "../Player/AutoPlayer.h"
#include "../Player/BasePlayer.h"
#include "../Player/HumanPlayer.h"

#include "../Utilities/Constants.h"

th::GameTable::GameTable() :
    gameNum(0),
    currSmallBlindPos(0),
    currSmallBlindChip(0)
{
}

bool th::GameTable::initPokerTable(const int32_t playerNum,
                                   const int32_t initChip,
                                   const int32_t smallBlindChip)
{
    if (playerNum < th::MINIMUM_PLAYER_NUM || playerNum >= th::MAXIMUM_PLAYER_NUM)
    {
        return false;
    }

    this->currSmallBlindChip = smallBlindChip;

    this->players.reserve(playerNum);
    this->players.push_back(std::make_shared<th::HumanPlayer>(0));
    this->players.back()->init(initChip);

    for (int32_t i = 1; i < playerNum; ++i)
    {
        this->players.push_back(std::make_shared<th::AutoPlayer>(i));
        this->players.back()->init(initChip);
    }

    this->cardDeck.init();

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
        this->cardDeck.shuffle();
        this->currGame.startGame(this->cardDeck, this->players);
    }
}

int32_t th::GameTable::getGameNum() const
{
    // for (const auto& player : this->players)
    // {
    //     player->showStatus();
    //     player->showHandCards();
    // }

    return this->gameNum;
}
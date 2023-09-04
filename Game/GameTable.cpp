#include "GameTable.h"

#include "Player/AutoPlayer.h"
#include "Player/BasePlayer.h"
#include "Player/HumanPlayer.h"

#include "Utilities/Constants.h"

th::GameTable::GameTable() :
    gameNum(0),
    curSmallBlindPos(0),
    curSmallBlindChip(0)
{
}

bool th::GameTable::initPokerTable(const int32_t   playerNum,
                                   const th::chip& initChip,
                                   const th::chip& smallBlindChip)
{
    if (playerNum < th::MINIMUM_PLAYER_NUM || playerNum >= th::MAXIMUM_PLAYER_NUM)
    {
        return false;
    }

    this->curSmallBlindChip = smallBlindChip;

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

    if (this->curGame.initGame(this->curSmallBlindPos, this->curSmallBlindChip) == true)
    {
        this->cardDeck.shuffle();
        this->curGame.startGame(this->cardDeck, this->players);
    }
}

int32_t th::GameTable::getGameNum() const
{
    return this->gameNum;
}
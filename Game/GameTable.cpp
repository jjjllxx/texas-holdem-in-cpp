#include "GameTable.h"

#include "Game.h"
#include "Player/AutoPlayer.h"
#include "Player/BasePlayer.h"
#include "Player/HumanPlayer.h"
#include "Utilities/Constants.h"

#include <iostream>

bool th::GameTable::initTable(const std::size_t playerNum,
                              const th::chip&   initChip,
                              const th::chip&   smallBlindChip)
{
    if (playerNum < th::MINIMUM_PLAYER_NUM || playerNum >= th::MAXIMUM_PLAYER_NUM)
    {
        std::cout << "INVALID number of players!" << std::endl;
        return false;
    }

    this->curSmallBlindChip = smallBlindChip;

    this->players.reserve(playerNum);
    this->players.push_back(std::make_shared<th::HumanPlayer>(0));
    this->players.back()->init(initChip);

    for (std::size_t i = 1; i < playerNum; ++i)
    {
        this->players.push_back(std::make_shared<th::AutoPlayer>(i));
        this->players.back()->init(initChip);
    }

    this->cardDeck.init();
    this->gameNum = 0;

    return true;
}

void th::GameTable::clearTable()
{
    this->players.clear();
}

bool th::GameTable::startANewGame()
{
    this->gameNum++;

    for (std::shared_ptr<th::BasePlayer>& player : this->players)
    {
        player->prepareForNextGame();
    }

    if (th::Game newGame;
        newGame.initGame(this->players.size(),
                         this->curSmallBlindPos,
                         this->curSmallBlindChip)
        == true)
    {
        newGame.startGame(this->cardDeck, this->players);
        this->curSmallBlindPos++;

        return true;
    }

    return false;
}

std::size_t th::GameTable::getGameNum() const
{
    return this->gameNum;
}
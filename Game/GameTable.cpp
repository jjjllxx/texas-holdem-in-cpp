#include "GameTable.h"

#include "Common/Logger/Logger.h"
#include "Game.h"
#include "Player/AutoPlayer.h"
#include "Player/BasePlayer.h"
#include "Player/HumanPlayer.h"
#include "Entity/Constants.h"

#include <iostream>

bool th::GameTable::initTable(const std::size_t playersCnt,
                              const th::chip&   initChip,
                              const th::chip&   smallBlindChip)
{
    if (playersCnt < th::MINIMUM_PLAYER_NUM || playersCnt >= th::MAXIMUM_PLAYER_NUM)
    {
        lgw("INVALID number of players!");
        return false;
    }

    this->smallBlindChip = smallBlindChip;

    this->players.reserve(playersCnt);
    this->players.push_back(std::make_shared<th::HumanPlayer>(0));
    this->players.back()->init(initChip);

    for (std::size_t i = 1; i < playersCnt; ++i)
    {
        this->players.push_back(std::make_shared<th::AutoPlayer>(i));
        this->players.back()->init(initChip);
    }

    this->cardDeck.init();
    this->gameNum          = 0;
    this->smallBlindPos    = 0;

    lgi("Game table initialised successfully!");

    return true;
}

void th::GameTable::clearTable()
{
    this->players.clear();
}

bool th::GameTable::startANewGame()
{
    for (std::shared_ptr<th::BasePlayer>& player : this->players)
    {
        player->prepareForNextGame();
    }

    if (th::Game newGame;
        newGame.initGame(this->players.size(),
                         this->smallBlindPos,
                         this->smallBlindChip)
        == true)
    {
        this->gameNum++;
        newGame.startGame(this->cardDeck, this->players);
        this->smallBlindPos++;

        return true;
    }

    return false;
}

std::size_t th::GameTable::getGameNum() const
{
    return this->gameNum;
}
#include "GameTable.h"

#include "Common/Logger/Logger.h"
#include "Core/Player/AutoPlayer.h"
#include "Core/Player/HumanPlayer.h"
#include "Entity/Constants.h"
#include "Game.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

bool th::GameTable::init()
{
    std::ifstream        gameConfig("../config/Game.json");
    const nlohmann::json json = nlohmann::json::parse(gameConfig);

    const std::size_t playersCnt = json["player_num"];
    const th::chip    initChip   = json["initial_chip"].get<int>();
    this->smallBlindChip         = json["initial_small_blind_chip"].get<int>();

    if (playersCnt < th::MINIMUM_PLAYER_NUM || playersCnt > th::MAXIMUM_PLAYER_NUM)
    {
        lge("INVALID number of players!");
        return false;
    }

    this->players.reserve(playersCnt);
    this->players.push_back(std::make_shared<th::HumanPlayer>(0));
    this->players.back()->init(initChip);

    for (std::size_t i = 1; i < playersCnt; ++i)
    {
        this->players.push_back(std::make_shared<th::AutoPlayer>(i));
        this->players.back()->init(initChip);
    }

    this->cardDeck.init();
    this->gameNum       = 0;
    this->smallBlindPos = 0;

    lgi("Game table initialised successfully!");

    return true;
}

void th::GameTable::clear()
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
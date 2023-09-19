#include "GameTable.h"

#include "Algorithms/Random.h"
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
    this->totalGameNum           = json["game_num_to_play"];

    gameConfig.close();

    if (th::GameTable::initPlayers(playersCnt, initChip) == false)
    {
        return false;
    }

    this->cardDeck.init();
    this->curGameNum    = 0;
    this->smallBlindPos = 0;

    lgi("Game table initialised successfully!");

    return true;
}

void th::GameTable::start()
{
    while (this->curGameNum < this->totalGameNum)
    {
        lgi("Game {} starts...", this->curGameNum);
        if (th::GameTable::startANewGame() == false)
        {
            lgi("Failed to start game {}, exit...", this->curGameNum);
            return;
        }
    }
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
        this->curGameNum++;
        newGame.startGame(this->cardDeck, this->players);
        this->smallBlindPos++;

        return true;
    }

    return false;
}

bool th::GameTable::initPlayers(const std::size_t playersCnt,
                                const th::chip&   initChip)
{
    if (playersCnt < th::MINIMUM_PLAYER_NUM || playersCnt > th::MAXIMUM_PLAYER_NUM)
    {
        lge("INVALID number of players!");
        return false;
    }

    this->players.reserve(playersCnt);
    const std::size_t humanPos = th::Random::generateWithin<std::size_t>(0, playersCnt);

    for (std::size_t i = 0; i < playersCnt; ++i)
    {
        i == humanPos
            ? this->players.push_back(std::make_shared<th::HumanPlayer>(i))
            : this->players.push_back(std::make_shared<th::AutoPlayer>(i));
        this->players.back()->init(initChip);
    }

    return true;
}
#pragma once

#include "Entity/Card/CardDeck.h"
#include "Game.h"

#include <memory>
#include <vector>

namespace th
{
class BasePlayer;

class GameTable
{
public:
    bool initTable(const std::size_t playerNum,
                   const th::chip&   initChip,
                   const th::chip&   smallBlindChip);
    void clearTable();

    void    startANewGame();
    std::size_t getGameNum() const;

private:
    std::size_t  gameNum;
    th::Game     curGame;
    th::CardDeck cardDeck;

    std::size_t curSmallBlindPos;
    th::chip    curSmallBlindChip;

    std::vector<std::shared_ptr<th::BasePlayer>> players;
};
} // namespace th

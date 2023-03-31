#pragma once

#include "../Card/CardDeck.h"
#include "Game.h"

#include <memory>
#include <vector>

namespace th
{
class BasePlayer;

class GameTable
{
public:
    GameTable();
    ~GameTable() = default;

    bool initPokerTable(const int32_t   playerNum,
                        const th::chip& initChip,
                        const th::chip& smallBlindChip);
    void clearPokerTable();

    void    startANewGame();
    int32_t getGameNum() const;

private:
    int32_t      gameNum;
    th::Game     currGame;
    th::CardDeck cardDeck;

    std::size_t currSmallBlindPos;
    th::chip    currSmallBlindChip;

    std::vector<std::shared_ptr<th::BasePlayer>> players;
};
} // namespace th

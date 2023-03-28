#pragma once

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

    bool initPokerTable(const int32_t playerNum,
                        const int32_t initChip,
                        const int32_t smallBlindChip);
    void clearPokerTable();

    void    startANewGame();
    int32_t getGameNum() const;

private:
    const int32_t MINIMUM_PLAYER_NUM;
    const int32_t MAXIMUM_PLAYER_NUM;

    int32_t  gameNum;
    th::Game currGame;

    std::size_t currSmallBlindPos;
    int32_t     currSmallBlindChip;

    std::vector<std::shared_ptr<th::BasePlayer>> players;
};
} // namespace th

#pragma once

#include "../Player/BasePlayer.h"
#include <memory>
#include <vector>

namespace th
{

class GameProcess
{
public:
    GameProcess();
    ~GameProcess() = default;

    bool initPokerTable(const int32_t playerNum,
                        const int32_t initChip);
    void clearPokerTable();

    void    startANewGame();
    int32_t getCurrPool() const;
    int32_t getGameRound() const;

private:
    const int32_t MINIMUM_PLAYER_NUM;
    const int32_t MAXIMUM_PLAYER_NUM;

    int32_t currPool;
    int32_t gameRound;

    std::vector<std::shared_ptr<th::BasePlayer>> players;
};
} // namespace th

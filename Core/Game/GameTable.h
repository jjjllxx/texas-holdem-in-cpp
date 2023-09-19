#pragma once

#include "Entity/Card/CardDeck.h"
#include "Entity/Chip/Chip.h"

#include <memory>
#include <vector>

namespace th
{
class BasePlayer;

class GameTable
{
public:
    bool init();
    void start();
    void clear();

private:
    std::size_t  curGameNum;
    std::size_t  totalGameNum;
    std::size_t  smallBlindPos;
    th::chip     smallBlindChip;
    th::CardDeck cardDeck;

    std::vector<std::shared_ptr<th::BasePlayer>> players;

    bool initPlayers(const std::size_t playersCnt,
                     const th::chip&   initChip);
    bool startANewGame();
};
} // namespace th

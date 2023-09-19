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
    void clear();

    bool        startANewGame();
    std::size_t getGameNum() const;

private:
    std::size_t  gameNum;
    std::size_t  smallBlindPos;
    th::chip     smallBlindChip;
    th::CardDeck cardDeck;

    std::vector<std::shared_ptr<th::BasePlayer>> players;

    bool initPlayers(const std::size_t playersCnt,
                     const th::chip&   initChip);
};
} // namespace th

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
    bool initTable(const std::size_t playerNum,
                   const th::chip&   initChip,
                   const th::chip&   smallBlindChip);
    void clearTable();

    bool        startANewGame();
    std::size_t getGameNum() const;

private:
    std::size_t  gameNum;
    std::size_t  curSmallBlindPos;
    th::chip     curSmallBlindChip;
    th::CardDeck cardDeck;

    std::vector<std::shared_ptr<th::BasePlayer>> players;
};
} // namespace th

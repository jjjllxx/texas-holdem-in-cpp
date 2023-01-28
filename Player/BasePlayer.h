#pragma once

#include "../Card/PokerCard.h"

#include <stdint.h>
#include <string>

namespace th
{
class BasePlayer
{
public:
    BasePlayer(const int32_t id);
    ~BasePlayer() = default;

    void init(const int32_t initNum);

    int32_t checkChip();
    void    addChip(const int32_t chipNum);
    void    minusChip(const int32_t chipNum);

    virtual int32_t raise(const int32_t chipNum) = 0;

    void    call(const int32_t currBet);
    void    fold();
    int32_t allIn();

    bool isAllIn();
    bool hasGivenUp();

private:
    int32_t     id;
    std::string name;

    int32_t chip;
    bool    hasGivenUpCurrGame;
    bool    hasAllIn;

    th::PokerCard firstHandCard;
    th::PokerCard secondHandCard;
};
} // namespace th
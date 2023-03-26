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

    int32_t checkChip() const;

    virtual int32_t raise(const int32_t chipNum) = 0;
    int32_t         call(const int32_t currBet);
    int32_t         allIn();

    void fold();

    bool isAllIn();
    bool hasGivenUp();

    void addChip(const int32_t chipNum);
    void minusChip(const int32_t chipNum);

    int32_t getId() const;
    virtual void showStatus() const = 0;

protected:
    int32_t     id;
    std::string name;

    int32_t chip;
    bool    hasGivenUpCurrGame;
    bool    hasAllIn;

    th::PokerCard firstHandCard;
    th::PokerCard secondHandCard;
};
} // namespace th
#pragma once

#include "../Card/PokerCard.h"

#include <stdint.h>

namespace th
{
class BasePlayer
{
public:
    BasePlayer(const int32_t id);
    ~BasePlayer() = default;

    void init(const int32_t chipNum);

    int32_t checkChip() const;

    int32_t         call(const int32_t currBet);
    int32_t         allIn();
    void            fold();
    virtual int32_t raise(const int32_t chipNum) = 0;

    bool isAllIn() const;
    bool hasGivenUp() const;

    int32_t      getId() const;
    virtual void showStatus() const = 0;

protected:
    int32_t id;
    int32_t chip;

    bool hasGivenUpCurrGame;
    bool hasAllIn;

    th::PokerCard firstHandCard;
    th::PokerCard secondHandCard;

    void addChip(const int32_t chipNum);
    void minusChip(const int32_t chipNum);
};
} // namespace th
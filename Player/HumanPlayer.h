#pragma once

#include "BasePlayer.h"

#include <iostream>

namespace th
{
class HumanPlayer final : public BasePlayer
{
public:
    HumanPlayer(const int32_t id);
    int32_t takeAction(const int32_t currBet) override;
    int32_t raise(const int32_t currBet) override;
    void    showStatus() const override;
    void    peekHandCards() const;

private:
};
} // namespace th
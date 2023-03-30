#pragma once

#include "BasePlayer.h"

#include <iostream>

namespace th
{
class HumanPlayer final : public BasePlayer
{
public:
    HumanPlayer(const int32_t id);

    void    init(const int32_t chipNum) override;
    int32_t takeAction(const int32_t currBet) override;
    int32_t raise(const int32_t currBet) override;

private:
};
} // namespace th
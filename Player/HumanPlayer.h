#pragma once

#include "BasePlayer.h"

#include <iostream>

namespace th
{
struct Chip;

class HumanPlayer final : public BasePlayer
{
public:
    HumanPlayer(const int32_t id);

    void     init(const th::Chip& chipNum) override;
    th::Chip takeAction(const th::Chip& currBet) override;
    th::Chip raise(const th::Chip& currBet) override;
};
} // namespace th
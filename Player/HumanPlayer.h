#pragma once

#include "BasePlayer.h"

namespace th
{
struct chip;

class HumanPlayer final : public BasePlayer
{
public:
    HumanPlayer(const int32_t id);

    void init(const th::chip& chipNum) override;
    void takeAction(const th::chip& curBet) override;
    void raise(const th::chip& curBet) override;
};
} // namespace th
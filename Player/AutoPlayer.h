#pragma once

#include "BasePlayer.h"

namespace th
{
class AutoPlayer final : public BasePlayer
{
public:
    AutoPlayer(const int32_t id);

    void    init(const int32_t chipNum) override;
    int32_t takeAction(const int32_t currBet) override;
    int32_t raise(const int32_t currBet) override;
};
} // namespace th
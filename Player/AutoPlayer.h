#pragma once

#include "BasePlayer.h"

namespace th
{
class AutoPlayer final : public BasePlayer
{
public:
    AutoPlayer(const int32_t id);
    int32_t raise(const int32_t currBet) override;
};
} // namespace th
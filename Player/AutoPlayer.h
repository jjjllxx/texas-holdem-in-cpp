#pragma once

#include "BasePlayer.h"

namespace th
{
class AutoPlayer : public BasePlayer
{
public:
    int32_t raise(const int32_t currBet);
};
} // namespace th
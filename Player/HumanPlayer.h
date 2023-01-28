#pragma once

#include "BasePlayer.h"

#include <iostream>

namespace th
{
class HumanPlayer : public BasePlayer
{
public:
    int32_t raise(const int32_t currBet);

private:
};
} // namespace th
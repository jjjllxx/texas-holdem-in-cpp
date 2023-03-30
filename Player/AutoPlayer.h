#pragma once

#include "BasePlayer.h"

namespace th
{
struct Chip;

class AutoPlayer final : public BasePlayer
{
public:
    AutoPlayer(const int32_t id);

    void     init(const th::Chip& chipNum) override;
    th::Chip takeAction(const th::Chip& currBet) override;
    th::Chip raise(const th::Chip& currBet) override;
};
} // namespace th
#pragma once

#include "BasePlayer.h"

namespace th
{
struct chip;

class AutoPlayer final : public BasePlayer
{
public:
    AutoPlayer(const int32_t id);

    void     init(const th::chip& chipNum) override;
    th::chip takeAction(const th::chip& currBet) override;
    th::chip raise(const th::chip& currBet) override;
};
} // namespace th
#pragma once

#include <vector>

namespace th
{
struct PokerCard;

namespace HandSelection
{
    std::vector<th::PokerCard> selectHighestHand(const std::vector<th::PokerCard>& fromCards);
} // namespace HandSelection
} // namespace th
#pragma once

#include <vector>

namespace th
{
struct PokerCard;

namespace CardSelection
{
    std::vector<th::PokerCard> selectHighestCardCombo(const std::vector<th::PokerCard>& fromCards);
} // namespace CardSelection
} // namespace th
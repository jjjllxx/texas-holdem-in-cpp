#pragma once

#include <vector>

namespace th
{
struct PokerCard;

namespace CardSelector
{
    std::vector<th::PokerCard> selectHighestCardCombo(const std::vector<th::PokerCard>& fromCards);
} // namespace CardSelector
} // namespace th
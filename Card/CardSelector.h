#pragma once

#include <vector>

namespace th
{
struct PokerCard;

namespace CardSelector
{
    std::vector<th::PokerCard> selectHighestCardCombo(const std::vector<th::PokerCard>& fromCards);

    void selectFiveCards(const std::size_t                 pos,
                         const std::vector<th::PokerCard>& fromCards,
                         std::vector<th::PokerCard>&       currHighest,
                         std::vector<th::PokerCard>&       currSelected);

    std::vector<th::PokerCard> selectTheHigher(const std::vector<th::PokerCard>& firstCards,
                                               const std::vector<th::PokerCard>& secondCards);
} // namespace CardSelector
} // namespace th
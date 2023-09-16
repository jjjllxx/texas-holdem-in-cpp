#include "CardSelection.h"

#include "Entity/Card/PokerCard.h"

#include "CardComparison.h"
#include "Utilities/Constants.h"

#include <algorithm>

std::vector<th::PokerCard> th::CardSelection::selectHighestCardCombo(const std::vector<th::PokerCard>& fromCards)
{
    if (fromCards.size() <= th::STANDARD_CARD_COMBO_SIZE)
    {
        return fromCards;
    }

    std::vector<th::PokerCard> highest(fromCards.begin(), fromCards.begin() + th::STANDARD_CARD_COMBO_SIZE);
    std::vector<bool>          bitmask(fromCards.size(), false);
    std::fill(bitmask.begin(), bitmask.begin() + th::STANDARD_CARD_COMBO_SIZE, true);

    while (std::prev_permutation(bitmask.begin(), bitmask.end()) == true)
    {
        std::vector<th::PokerCard> curCombo;
        for (std::size_t i = 0; i < fromCards.size(); ++i)
        {
            if (bitmask[i] == true)
            {
                curCombo.push_back(fromCards[i]);
            }
        }

        if (th::CardComparison::compareCardCombo(curCombo, highest)
            == th::CardComboCmpResult::Win)
        {
            highest = curCombo;
        }
    }

    return highest;
}
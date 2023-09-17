#include "HandSelection.h"

#include "Entity/Card/PokerCard.h"

#include "HandComparison.h"
#include "Utilities/Constants.h"

#include <algorithm>

std::vector<th::PokerCard> th::HandSelection::selectHighestHand(const std::vector<th::PokerCard>& fromCards)
{
    if (fromCards.size() <= th::STANDARD_HAND_SIZE)
    {
        return fromCards;
    }

    std::vector<th::PokerCard> highest(fromCards.begin(), fromCards.begin() + th::STANDARD_HAND_SIZE);
    std::vector<bool>          bitmask(fromCards.size(), false);
    std::fill(bitmask.begin(), bitmask.begin() + th::STANDARD_HAND_SIZE, true);

    while (std::prev_permutation(bitmask.begin(), bitmask.end()) == true)
    {
        std::vector<th::PokerCard> curHand;
        for (std::size_t i = 0; i < fromCards.size(); ++i)
        {
            if (bitmask[i] == true)
            {
                curHand.push_back(fromCards[i]);
            }
        }

        if (th::HandComparison::compareHand(curHand, highest)
            == th::HandCmpResult::Win)
        {
            highest = curHand;
        }
    }

    return highest;
}
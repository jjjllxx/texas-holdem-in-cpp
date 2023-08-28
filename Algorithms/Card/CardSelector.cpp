#include "CardSelector.h"

#include "Entity/Card/PokerCard.h"

#include "CardComparison.h"

std::vector<th::PokerCard> th::CardSelector::selectHighestCardCombo(const std::vector<th::PokerCard>& fromCards)
{
    if (fromCards.size() <= 5)
    {
        return fromCards;
    }

    std::vector<th::PokerCard> currHighest = { fromCards[0], fromCards[1], fromCards[2], fromCards[3], fromCards[4] };
    std::vector<th::PokerCard> currSelected;

    th::CardSelector::selectFiveCards(0, fromCards, currHighest, currSelected);

    return currHighest;
}

void th::CardSelector::selectFiveCards(const std::size_t                 pos,
                                       const std::vector<th::PokerCard>& fromCards,
                                       std::vector<th::PokerCard>&       currHighest,
                                       std::vector<th::PokerCard>&       currSelected)
{
    // backtrack algorithm
    if (currSelected.size() == 5)
    {
        currHighest = th::CardSelector::selectTheHigher(currHighest, currSelected);

        return;
    }

    if (currSelected.size() + fromCards.size() - pos < 5)
    {
        // If select all the left cards and the currSelected will be still less than 5,
        // then it is not necessary to select further.
        return;
    }

    currSelected.push_back(fromCards[pos]);
    th::CardSelector::selectFiveCards(pos + 1, fromCards, currHighest, currSelected);
    currSelected.pop_back();
    th::CardSelector::selectFiveCards(pos + 1, fromCards, currHighest, currSelected);
}

std::vector<th::PokerCard> th::CardSelector::selectTheHigher(const std::vector<th::PokerCard>& firstCards,
                                                             const std::vector<th::PokerCard>& secondCards)
{
    const th::ComparisonResult result = th::CardComparison::compareCardCombo(firstCards, secondCards);

    switch (result)
    {
    case th::ComparisonResult::Win:
    case th::ComparisonResult::Draw:
        return firstCards;
    case th::ComparisonResult::Lose:
        return secondCards;
    case th::ComparisonResult::INVALID:
    default:
        return {};
    }
}
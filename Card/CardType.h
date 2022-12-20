#pragma once

#include "PokerCard.h"

#include <unordered_map>
#include <vector>

namespace th
{
    enum class CardComboType
    {
        INVALID,

        HighCard,
        OnePair,
        TwoPairs,
        ThreeOfAKind,
        Straight,
        Flush,
        FullOfHouse,
        FourOfAKind,
        StraightFlush
    };

    struct FiveCards
    {
        FiveCards();

        th::CardComboType type;
        std::vector<th::PokerCard> sortedCards;
    };

    namespace CardTypeUtility
    {
        th::FiveCards findHighestCardCombo(const std::vector<th::PokerCard>& fromCards);
        void          selectFiveCards(const std::vector<th::PokerCard>& fromCards,
                                      std::vector<th::PokerCard>&       selectedCards,
                                      std::size_t&                      pos);

        bool compareCardCombo();

        th::CardComboType judgeCardCombo(const std::vector<th::PokerCard>& fiveCards);
        bool isFlush(const std::vector<th::PokerCard>& fiveCards);
        bool isStraight(const std::vector<th::PokerCard>& fiveCards);
        bool isFourOfAKind(const std::unordered_map<int32_t, int32_t>& pointCount);
        bool isThreeOfKind(const std::unordered_map<int32_t, int32_t>& pointCount);
    }
    } // namespace th
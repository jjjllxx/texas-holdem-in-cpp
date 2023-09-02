#include <gtest/gtest.h>
#include <vector>

#include "CardSelector.h"
#include "Entity/Card/PokerCard.h"

namespace th
{
namespace CardSelector_Test
{
    const th::PokerCard HEART_A(th::CardSuit::Heart, 14);
    const th::PokerCard HEART_2(th::CardSuit::Heart, 2);
    const th::PokerCard HEART_3(th::CardSuit::Heart, 3);
    const th::PokerCard HEART_4(th::CardSuit::Heart, 4);
    const th::PokerCard HEART_5(th::CardSuit::Heart, 5);
    const th::PokerCard HEART_6(th::CardSuit::Heart, 6);
    const th::PokerCard CLUB_2(th::CardSuit::Club, 2);
} // namespace CardSelector_Test
} // namespace th

GTEST_TEST(Algorithms_Card_CardSelector, selectHighestCardCombo_size_less_than_6) // NOLINT
{
    const std::vector<th::PokerCard> highestCombo = th::CardSelector::selectHighestCardCombo({
        th::CardSelector_Test::CLUB_2,
        th::CardSelector_Test::HEART_2,
        th::CardSelector_Test::HEART_3,
        th::CardSelector_Test::HEART_4,
        th::CardSelector_Test::HEART_6,
    });

    EXPECT_EQ(highestCombo.size(), 5);
    EXPECT_EQ(highestCombo[0], th::CardSelector_Test::CLUB_2);
    EXPECT_EQ(highestCombo[1], th::CardSelector_Test::HEART_2);
    EXPECT_EQ(highestCombo[2], th::CardSelector_Test::HEART_3);
    EXPECT_EQ(highestCombo[3], th::CardSelector_Test::HEART_4);
    EXPECT_EQ(highestCombo[4], th::CardSelector_Test::HEART_6);
}

GTEST_TEST(Algorithms_Card_CardSelector, selectHighestCardCombo_size_7) // NOLINT
{
    const std::vector<th::PokerCard> highestCombo
        = th::CardSelector::selectHighestCardCombo({
            th::CardSelector_Test::HEART_4,
            th::CardSelector_Test::HEART_2,
            th::CardSelector_Test::HEART_3,
            th::CardSelector_Test::CLUB_2,
            th::CardSelector_Test::HEART_6,
            th::CardSelector_Test::HEART_A,
            th::CardSelector_Test::HEART_5,
        });

    EXPECT_EQ(highestCombo.size(), 5);
    EXPECT_EQ(highestCombo[0], th::CardSelector_Test::HEART_4);
    EXPECT_EQ(highestCombo[1], th::CardSelector_Test::HEART_2);
    EXPECT_EQ(highestCombo[2], th::CardSelector_Test::HEART_3);
    EXPECT_EQ(highestCombo[3], th::CardSelector_Test::HEART_6);
    EXPECT_EQ(highestCombo[4], th::CardSelector_Test::HEART_5);
}

#include <gtest/gtest.h>
#include <vector>

#include "Entity/Card/PokerCard.h"
#include "HandSelection.h"

namespace th
{
namespace HandSelection_Test
{
    const th::PokerCard HEART_A(th::CardSuit::Heart, 14);
    const th::PokerCard HEART_2(th::CardSuit::Heart, 2);
    const th::PokerCard HEART_3(th::CardSuit::Heart, 3);
    const th::PokerCard HEART_4(th::CardSuit::Heart, 4);
    const th::PokerCard HEART_5(th::CardSuit::Heart, 5);
    const th::PokerCard HEART_6(th::CardSuit::Heart, 6);
    const th::PokerCard CLUB_2(th::CardSuit::Club, 2);
} // namespace HandSelection_Test
} // namespace th

GTEST_TEST(Algorithms_Card_HandSelection, selectHighestHand_size_less_than_6) // NOLINT
{
    const std::vector<th::PokerCard> highestCombo = th::HandSelection::selectHighestHand({
        th::HandSelection_Test::CLUB_2,
        th::HandSelection_Test::HEART_2,
        th::HandSelection_Test::HEART_3,
        th::HandSelection_Test::HEART_4,
        th::HandSelection_Test::HEART_6,
    });

    EXPECT_EQ(highestCombo.size(), 5);
    EXPECT_EQ(highestCombo[0], th::HandSelection_Test::CLUB_2);
    EXPECT_EQ(highestCombo[1], th::HandSelection_Test::HEART_2);
    EXPECT_EQ(highestCombo[2], th::HandSelection_Test::HEART_3);
    EXPECT_EQ(highestCombo[3], th::HandSelection_Test::HEART_4);
    EXPECT_EQ(highestCombo[4], th::HandSelection_Test::HEART_6);
}

GTEST_TEST(Algorithms_Card_HandSelection, selectHighestHand_size_7) // NOLINT
{
    const std::vector<th::PokerCard> highestCombo
        = th::HandSelection::selectHighestHand({
            th::HandSelection_Test::HEART_4,
            th::HandSelection_Test::HEART_2,
            th::HandSelection_Test::HEART_3,
            th::HandSelection_Test::CLUB_2,
            th::HandSelection_Test::HEART_6,
            th::HandSelection_Test::HEART_A,
            th::HandSelection_Test::HEART_5,
        });

    EXPECT_EQ(highestCombo.size(), 5);
    EXPECT_EQ(highestCombo[0], th::HandSelection_Test::HEART_4);
    EXPECT_EQ(highestCombo[1], th::HandSelection_Test::HEART_2);
    EXPECT_EQ(highestCombo[2], th::HandSelection_Test::HEART_3);
    EXPECT_EQ(highestCombo[3], th::HandSelection_Test::HEART_6);
    EXPECT_EQ(highestCombo[4], th::HandSelection_Test::HEART_5);
}

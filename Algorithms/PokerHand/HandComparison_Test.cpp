#include <gtest/gtest.h>
#include <vector>

#include "Entity/Card/PokerCard.h"
#include "HandComparison.h"

namespace th
{
namespace HandCmp_Test
{
    const th::PokerCard HEART_A(th::CardSuit::Heart, 14);
    const th::PokerCard HEART_2(th::CardSuit::Heart, 2);
    const th::PokerCard HEART_3(th::CardSuit::Heart, 3);
    const th::PokerCard HEART_4(th::CardSuit::Heart, 4);
    const th::PokerCard HEART_5(th::CardSuit::Heart, 5);
    const th::PokerCard HEART_6(th::CardSuit::Heart, 6);
    const th::PokerCard DIAMOND_2(th::CardSuit::Diamond, 2);
    const th::PokerCard DIAMOND_3(th::CardSuit::Diamond, 3);
    const th::PokerCard DIAMOND_5(th::CardSuit::Diamond, 5);
    const th::PokerCard CLUB_2(th::CardSuit::Club, 2);
    const th::PokerCard CLUB_3(th::CardSuit::Club, 3);
    const th::PokerCard CLUB_4(th::CardSuit::Club, 4);
    const th::PokerCard CLUB_5(th::CardSuit::Club, 5);
    const th::PokerCard SPADE_2(th::CardSuit::Spade, 2);
    const th::PokerCard SPADE_3(th::CardSuit::Spade, 3);
} // namespace HandCmp_Test
} // namespace th

// To-Do: Test function deduceCardCmpOrder(). This function is currently not tested because it has many branches but simple logic.
// Its sub-functions are all tested.

GTEST_TEST(Algorithms_Card_HandComparison, compareHand_invalid) // NOLINT
{
    const th::HandCmpResult result = th::HandComparison::compareHand({ th::HandCmp_Test::HEART_3,
                                                                       th::HandCmp_Test::HEART_5,
                                                                       th::HandCmp_Test::HEART_2,
                                                                       th::HandCmp_Test::HEART_A },
                                                                     {});

    EXPECT_EQ(result, th::HandCmpResult::INVALID);
}

GTEST_TEST(Algorithms_Card_HandComparison, compareHand_win) // NOLINT
{
    const std::vector<th::PokerCard> firstHand = {
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondHand = {
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_6,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_2,
    };

    EXPECT_EQ(th::HandComparison::compareHand(firstHand, secondHand),
              th::HandCmpResult::Win);
}

GTEST_TEST(Algorithms_Card_HandComparison, compareHand_lose) // NOLINT
{
    const std::vector<th::PokerCard> firstHand = {
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondHand = {
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_6,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::HEART_2,
    };

    EXPECT_EQ(th::HandComparison::compareHand(firstHand, secondHand),
              th::HandCmpResult::Lose);
}

GTEST_TEST(Algorithms_Card_HandComparison, compareHand_same_type_win) // NOLINT
{
    const std::vector<th::PokerCard> firstHand = {
        th::HandCmp_Test::HEART_4,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondHand = {
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_2,
    };

    EXPECT_EQ(th::HandComparison::compareHand(firstHand, secondHand),
              th::HandCmpResult::Win);
}

GTEST_TEST(Algorithms_Card_HandComparison, compareHand_same_type_lose) // NOLINT
{
    const std::vector<th::PokerCard> firstHand = {
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondHand = {
        th::HandCmp_Test::HEART_4,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_3,
    };

    EXPECT_EQ(th::HandComparison::compareHand(firstHand, secondHand),
              th::HandCmpResult::Lose);
}

GTEST_TEST(Algorithms_Card_HandComparison, compareHand_draw) // NOLINT
{
    const std::vector<th::PokerCard> firstHand = {
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondHand = {
        th::HandCmp_Test::SPADE_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::DIAMOND_2,
    };

    EXPECT_EQ(th::HandComparison::compareHand(firstHand, secondHand),
              th::HandCmpResult::Draw);
}

GTEST_TEST(Algorithms_Card_HandComparison, sortCardsByPoint) // NOLINT
{
    const std::vector<th::PokerCard> sortedHand = th::HandComparison::sortHandByPoint({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::HEART_A,
        th::HandCmp_Test::HEART_4,
    });

    EXPECT_EQ(sortedHand.size(), 5);
    EXPECT_EQ(sortedHand[0].point, 14);
    EXPECT_EQ(sortedHand[1].point, 5);
    EXPECT_EQ(sortedHand[2].point, 4);
    EXPECT_EQ(sortedHand[3].point, 3);
    EXPECT_EQ(sortedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceOnePairOrder_54322) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceOnePairOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_2,
        th::HandCmp_Test::HEART_4,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 2);
    EXPECT_EQ(orderedHand[1].point, 2);
    EXPECT_EQ(orderedHand[2].point, 5);
    EXPECT_EQ(orderedHand[3].point, 4);
    EXPECT_EQ(orderedHand[4].point, 3);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceOnePairOrder_54332) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceOnePairOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_3,
        th::HandCmp_Test::HEART_4,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 3);
    EXPECT_EQ(orderedHand[1].point, 3);
    EXPECT_EQ(orderedHand[2].point, 5);
    EXPECT_EQ(orderedHand[3].point, 4);
    EXPECT_EQ(orderedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceOnePairOrder_54432) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceOnePairOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_4,
        th::HandCmp_Test::HEART_4,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 4);
    EXPECT_EQ(orderedHand[1].point, 4);
    EXPECT_EQ(orderedHand[2].point, 5);
    EXPECT_EQ(orderedHand[3].point, 3);
    EXPECT_EQ(orderedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceOnePairOrder_55432) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceOnePairOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_5,
        th::HandCmp_Test::HEART_4,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 5);
    EXPECT_EQ(orderedHand[1].point, 5);
    EXPECT_EQ(orderedHand[2].point, 4);
    EXPECT_EQ(orderedHand[3].point, 3);
    EXPECT_EQ(orderedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceTwoPairsOrder_53322) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceTwoPairsOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_3,
        th::HandCmp_Test::CLUB_2,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 3);
    EXPECT_EQ(orderedHand[1].point, 3);
    EXPECT_EQ(orderedHand[2].point, 2);
    EXPECT_EQ(orderedHand[3].point, 2);
    EXPECT_EQ(orderedHand[4].point, 5);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceTwoPairsOrder_55322) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceTwoPairsOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_5,
        th::HandCmp_Test::CLUB_2,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 5);
    EXPECT_EQ(orderedHand[1].point, 5);
    EXPECT_EQ(orderedHand[2].point, 2);
    EXPECT_EQ(orderedHand[3].point, 2);
    EXPECT_EQ(orderedHand[4].point, 3);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceTwoPairsOrder_55332) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceTwoPairsOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_5,
        th::HandCmp_Test::CLUB_3,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 5);
    EXPECT_EQ(orderedHand[1].point, 5);
    EXPECT_EQ(orderedHand[2].point, 3);
    EXPECT_EQ(orderedHand[3].point, 3);
    EXPECT_EQ(orderedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceThreeOfAKindOrder_53222) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceThreeOfAKindOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_2,
        th::HandCmp_Test::DIAMOND_2,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 2);
    EXPECT_EQ(orderedHand[1].point, 2);
    EXPECT_EQ(orderedHand[2].point, 2);
    EXPECT_EQ(orderedHand[3].point, 5);
    EXPECT_EQ(orderedHand[4].point, 3);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceThreeOfAKindOrder_53332) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceThreeOfAKindOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::DIAMOND_3,
        th::HandCmp_Test::CLUB_3,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 3);
    EXPECT_EQ(orderedHand[1].point, 3);
    EXPECT_EQ(orderedHand[2].point, 3);
    EXPECT_EQ(orderedHand[3].point, 5);
    EXPECT_EQ(orderedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceThreeOfAKindOrder_55532) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceThreeOfAKindOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::DIAMOND_5,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_5,
        th::HandCmp_Test::HEART_5,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 5);
    EXPECT_EQ(orderedHand[1].point, 5);
    EXPECT_EQ(orderedHand[2].point, 5);
    EXPECT_EQ(orderedHand[3].point, 3);
    EXPECT_EQ(orderedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceStraightOrder_A2345) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceStraightOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::CLUB_4,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_5,
        th::HandCmp_Test::HEART_A,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 5);
    EXPECT_EQ(orderedHand[1].point, 4);
    EXPECT_EQ(orderedHand[2].point, 3);
    EXPECT_EQ(orderedHand[3].point, 2);
    EXPECT_EQ(orderedHand[4].point, 14);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceStraightOrder_normal) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceStraightOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::HEART_6,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_4,
        th::HandCmp_Test::DIAMOND_5,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 6);
    EXPECT_EQ(orderedHand[1].point, 5);
    EXPECT_EQ(orderedHand[2].point, 4);
    EXPECT_EQ(orderedHand[3].point, 3);
    EXPECT_EQ(orderedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceFullOfHouseOrder_33222) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceFullOfHouseOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::CLUB_3,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::CLUB_2,
        th::HandCmp_Test::DIAMOND_2,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 2);
    EXPECT_EQ(orderedHand[1].point, 2);
    EXPECT_EQ(orderedHand[2].point, 2);
    EXPECT_EQ(orderedHand[3].point, 3);
    EXPECT_EQ(orderedHand[4].point, 3);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceFullOfHouseOrder_33322) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceFullOfHouseOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::CLUB_3,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::DIAMOND_3,
        th::HandCmp_Test::DIAMOND_2,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 3);
    EXPECT_EQ(orderedHand[1].point, 3);
    EXPECT_EQ(orderedHand[2].point, 3);
    EXPECT_EQ(orderedHand[3].point, 2);
    EXPECT_EQ(orderedHand[4].point, 2);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceFourOfAKindOrder_32222) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceFourOfAKindOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::CLUB_2,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::SPADE_2,
        th::HandCmp_Test::DIAMOND_2,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 2);
    EXPECT_EQ(orderedHand[1].point, 2);
    EXPECT_EQ(orderedHand[2].point, 2);
    EXPECT_EQ(orderedHand[3].point, 2);
    EXPECT_EQ(orderedHand[4].point, 3);
}

GTEST_TEST(Algorithms_Card_HandComparison, deduceFourOfAKindOrder_33332) // NOLINT
{
    const std::vector<th::PokerCard> orderedHand = th::HandComparison::deduceFourOfAKindOrder({
        th::HandCmp_Test::HEART_3,
        th::HandCmp_Test::CLUB_3,
        th::HandCmp_Test::HEART_2,
        th::HandCmp_Test::DIAMOND_3,
        th::HandCmp_Test::SPADE_3,
    });

    EXPECT_EQ(orderedHand.size(), 5);
    EXPECT_EQ(orderedHand[0].point, 3);
    EXPECT_EQ(orderedHand[1].point, 3);
    EXPECT_EQ(orderedHand[2].point, 3);
    EXPECT_EQ(orderedHand[3].point, 3);
    EXPECT_EQ(orderedHand[4].point, 2);
}
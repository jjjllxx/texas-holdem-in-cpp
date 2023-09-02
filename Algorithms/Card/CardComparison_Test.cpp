#include <gtest/gtest.h>
#include <vector>

#include "CardComparison.h"
#include "Entity/Card/PokerCard.h"

namespace th
{
namespace CardCmp_Test
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
} // namespace CardCmp_Test
} // namespace th

// To-Do: Test function deduceCardCmpOrder(). This function is currently not tested because it has many branches but simple logic.
// Its sub-functions are all tested.

GTEST_TEST(Algorithms_Card_CardComparison, compareCardCombo_invalid) // NOLINT
{
    const th::CardComboCmpResult result = th::CardComparison::compareCardCombo({ th::CardCmp_Test::HEART_3,
                                                                                 th::CardCmp_Test::HEART_5,
                                                                                 th::CardCmp_Test::HEART_2,
                                                                                 th::CardCmp_Test::HEART_A },
                                                                               {});

    EXPECT_EQ(result, th::CardComboCmpResult::INVALID);
}

GTEST_TEST(Algorithms_Card_CardComparison, compareCardCombo_win) // NOLINT
{
    const std::vector<th::PokerCard> firstCards = {
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondCards = {
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_6,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_2,
    };

    EXPECT_EQ(th::CardComparison::compareCardCombo(firstCards, secondCards),
              th::CardComboCmpResult::Win);
}

GTEST_TEST(Algorithms_Card_CardComparison, compareCardCombo_lose) // NOLINT
{
    const std::vector<th::PokerCard> firstCards = {
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondCards = {
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_6,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::HEART_2,
    };

    EXPECT_EQ(th::CardComparison::compareCardCombo(firstCards, secondCards),
              th::CardComboCmpResult::Lose);
}

GTEST_TEST(Algorithms_Card_CardComparison, compareCardCombo_same_type_win) // NOLINT
{
    const std::vector<th::PokerCard> firstCards = {
        th::CardCmp_Test::HEART_4,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondCards = {
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_2,
    };

    EXPECT_EQ(th::CardComparison::compareCardCombo(firstCards, secondCards),
              th::CardComboCmpResult::Win);
}

GTEST_TEST(Algorithms_Card_CardComparison, compareCardCombo_same_type_lose) // NOLINT
{
    const std::vector<th::PokerCard> firstCards = {
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondCards = {
        th::CardCmp_Test::HEART_4,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_3,
    };

    EXPECT_EQ(th::CardComparison::compareCardCombo(firstCards, secondCards),
              th::CardComboCmpResult::Lose);
}

GTEST_TEST(Algorithms_Card_CardComparison, compareCardCombo_draw) // NOLINT
{
    const std::vector<th::PokerCard> firstCards = {
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_2,
    };

    const std::vector<th::PokerCard> secondCards = {
        th::CardCmp_Test::SPADE_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::DIAMOND_2,
    };

    EXPECT_EQ(th::CardComparison::compareCardCombo(firstCards, secondCards),
              th::CardComboCmpResult::Draw);
}

GTEST_TEST(Algorithms_Card_CardComparison, sortCardsByPoint) // NOLINT
{
    const std::vector<th::PokerCard> sortedCards = th::CardComparison::sortCardsByPoint({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::HEART_A,
        th::CardCmp_Test::HEART_4,
    });

    EXPECT_EQ(sortedCards.size(), 5);
    EXPECT_EQ(sortedCards[0].point, 14);
    EXPECT_EQ(sortedCards[1].point, 5);
    EXPECT_EQ(sortedCards[2].point, 4);
    EXPECT_EQ(sortedCards[3].point, 3);
    EXPECT_EQ(sortedCards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceOnePairOrder_54322) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceOnePairOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_2,
        th::CardCmp_Test::HEART_4,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 2);
    EXPECT_EQ(cards[1].point, 2);
    EXPECT_EQ(cards[2].point, 5);
    EXPECT_EQ(cards[3].point, 4);
    EXPECT_EQ(cards[4].point, 3);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceOnePairOrder_54332) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceOnePairOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_3,
        th::CardCmp_Test::HEART_4,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 3);
    EXPECT_EQ(cards[1].point, 3);
    EXPECT_EQ(cards[2].point, 5);
    EXPECT_EQ(cards[3].point, 4);
    EXPECT_EQ(cards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceOnePairOrder_54432) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceOnePairOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_4,
        th::CardCmp_Test::HEART_4,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 4);
    EXPECT_EQ(cards[1].point, 4);
    EXPECT_EQ(cards[2].point, 5);
    EXPECT_EQ(cards[3].point, 3);
    EXPECT_EQ(cards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceOnePairOrder_55432) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceOnePairOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_5,
        th::CardCmp_Test::HEART_4,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 5);
    EXPECT_EQ(cards[1].point, 5);
    EXPECT_EQ(cards[2].point, 4);
    EXPECT_EQ(cards[3].point, 3);
    EXPECT_EQ(cards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceTwoPairsOrder_53322) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceTwoPairsOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_3,
        th::CardCmp_Test::CLUB_2,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 3);
    EXPECT_EQ(cards[1].point, 3);
    EXPECT_EQ(cards[2].point, 2);
    EXPECT_EQ(cards[3].point, 2);
    EXPECT_EQ(cards[4].point, 5);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceTwoPairsOrder_55322) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceTwoPairsOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_5,
        th::CardCmp_Test::CLUB_2,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 5);
    EXPECT_EQ(cards[1].point, 5);
    EXPECT_EQ(cards[2].point, 2);
    EXPECT_EQ(cards[3].point, 2);
    EXPECT_EQ(cards[4].point, 3);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceTwoPairsOrder_55332) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceTwoPairsOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_5,
        th::CardCmp_Test::CLUB_3,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 5);
    EXPECT_EQ(cards[1].point, 5);
    EXPECT_EQ(cards[2].point, 3);
    EXPECT_EQ(cards[3].point, 3);
    EXPECT_EQ(cards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceThreeOfAKindOrder_53222) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceThreeOfAKindOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_2,
        th::CardCmp_Test::DIAMOND_2,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 2);
    EXPECT_EQ(cards[1].point, 2);
    EXPECT_EQ(cards[2].point, 2);
    EXPECT_EQ(cards[3].point, 5);
    EXPECT_EQ(cards[4].point, 3);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceThreeOfAKindOrder_53332) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceThreeOfAKindOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::DIAMOND_3,
        th::CardCmp_Test::CLUB_3,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 3);
    EXPECT_EQ(cards[1].point, 3);
    EXPECT_EQ(cards[2].point, 3);
    EXPECT_EQ(cards[3].point, 5);
    EXPECT_EQ(cards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceThreeOfAKindOrder_55532) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceThreeOfAKindOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::DIAMOND_5,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_5,
        th::CardCmp_Test::HEART_5,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 5);
    EXPECT_EQ(cards[1].point, 5);
    EXPECT_EQ(cards[2].point, 5);
    EXPECT_EQ(cards[3].point, 3);
    EXPECT_EQ(cards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceStraightOrder_A2345) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceStraightOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::CLUB_4,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_5,
        th::CardCmp_Test::HEART_A,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 5);
    EXPECT_EQ(cards[1].point, 4);
    EXPECT_EQ(cards[2].point, 3);
    EXPECT_EQ(cards[3].point, 2);
    EXPECT_EQ(cards[4].point, 14);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceStraightOrder_normal) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceStraightOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::HEART_6,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_4,
        th::CardCmp_Test::DIAMOND_5,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 6);
    EXPECT_EQ(cards[1].point, 5);
    EXPECT_EQ(cards[2].point, 4);
    EXPECT_EQ(cards[3].point, 3);
    EXPECT_EQ(cards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceFullOfHouseOrder_33222) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceFullOfHouseOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::CLUB_3,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::CLUB_2,
        th::CardCmp_Test::DIAMOND_2,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 2);
    EXPECT_EQ(cards[1].point, 2);
    EXPECT_EQ(cards[2].point, 2);
    EXPECT_EQ(cards[3].point, 3);
    EXPECT_EQ(cards[4].point, 3);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceFullOfHouseOrder_33322) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceFullOfHouseOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::CLUB_3,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::DIAMOND_3,
        th::CardCmp_Test::DIAMOND_2,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 3);
    EXPECT_EQ(cards[1].point, 3);
    EXPECT_EQ(cards[2].point, 3);
    EXPECT_EQ(cards[3].point, 2);
    EXPECT_EQ(cards[4].point, 2);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceFourOfAKindOrder_32222) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceFourOfAKindOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::CLUB_2,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::SPADE_2,
        th::CardCmp_Test::DIAMOND_2,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 2);
    EXPECT_EQ(cards[1].point, 2);
    EXPECT_EQ(cards[2].point, 2);
    EXPECT_EQ(cards[3].point, 2);
    EXPECT_EQ(cards[4].point, 3);
}

GTEST_TEST(Algorithms_Card_CardComparison, deduceFourOfAKindOrder_33332) // NOLINT
{
    const std::vector<th::PokerCard> cards = th::CardComparison::deduceFourOfAKindOrder({
        th::CardCmp_Test::HEART_3,
        th::CardCmp_Test::CLUB_3,
        th::CardCmp_Test::HEART_2,
        th::CardCmp_Test::DIAMOND_3,
        th::CardCmp_Test::SPADE_3,
    });

    EXPECT_EQ(cards.size(), 5);
    EXPECT_EQ(cards[0].point, 3);
    EXPECT_EQ(cards[1].point, 3);
    EXPECT_EQ(cards[2].point, 3);
    EXPECT_EQ(cards[3].point, 3);
    EXPECT_EQ(cards[4].point, 2);
}
#include <gtest/gtest.h>

#include "Entity/Card/PokerCard.h"
#include "HandType.h"

namespace th
{
namespace HandType_Test
{
    const th::PokerCard HEART_A(th::CardSuit::Heart, 14);
    const th::PokerCard HEART_2(th::CardSuit::Heart, 2);
    const th::PokerCard HEART_3(th::CardSuit::Heart, 3);
    const th::PokerCard HEART_4(th::CardSuit::Heart, 4);
    const th::PokerCard HEART_5(th::CardSuit::Heart, 5);
    const th::PokerCard HEART_6(th::CardSuit::Heart, 6);
    const th::PokerCard DIAMOND_A(th::CardSuit::Diamond, 14);
    const th::PokerCard CLUB_A(th::CardSuit::Club, 14);
    const th::PokerCard CLUB_2(th::CardSuit::Club, 2);
    const th::PokerCard SPADE_A(th::CardSuit::Spade, 14);
} // namespace HandType_Test
} // namespace th

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_invalid) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::DIAMOND_A,
                  th::HandType_Test::HEART_A,
                  th::HandType_Test::HEART_2,
                  th::HandType_Test::CLUB_2,
              }),
              th::PokerHandType::INVALID);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_high_card) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::CLUB_A,
                  th::HandType_Test::HEART_2,
                  th::HandType_Test::HEART_3,
                  th::HandType_Test::HEART_4,
                  th::HandType_Test::HEART_6,
              }),
              th::PokerHandType::HighCard);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_one_pair) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::CLUB_A,
                  th::HandType_Test::HEART_A,
                  th::HandType_Test::HEART_3,
                  th::HandType_Test::HEART_4,
                  th::HandType_Test::HEART_6,
              }),
              th::PokerHandType::OnePair);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_two_pairs) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::DIAMOND_A,
                  th::HandType_Test::HEART_A,
                  th::HandType_Test::HEART_2,
                  th::HandType_Test::CLUB_2,
                  th::HandType_Test::HEART_6,
              }),
              th::PokerHandType::TwoPairs);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_three_of_a_kind) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::DIAMOND_A,
                  th::HandType_Test::HEART_A,
                  th::HandType_Test::CLUB_A,
                  th::HandType_Test::CLUB_2,
                  th::HandType_Test::HEART_6,
              }),
              th::PokerHandType::ThreeOfAKind);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_straight) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::CLUB_2,
                  th::HandType_Test::HEART_5,
                  th::HandType_Test::HEART_3,
                  th::HandType_Test::HEART_6,
                  th::HandType_Test::HEART_4,
              }),
              th::PokerHandType::Straight);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_flush) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::HEART_A,
                  th::HandType_Test::HEART_5,
                  th::HandType_Test::HEART_3,
                  th::HandType_Test::HEART_6,
                  th::HandType_Test::HEART_4,
              }),
              th::PokerHandType::Flush);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_full_of_house) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::DIAMOND_A,
                  th::HandType_Test::HEART_A,
                  th::HandType_Test::CLUB_A,
                  th::HandType_Test::CLUB_2,
                  th::HandType_Test::HEART_2,
              }),
              th::PokerHandType::FullOfHouse);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_four_of_a_kind) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::DIAMOND_A,
                  th::HandType_Test::HEART_A,
                  th::HandType_Test::CLUB_A,
                  th::HandType_Test::SPADE_A,
                  th::HandType_Test::HEART_2,
              }),
              th::PokerHandType::FourOfAKind);
}

GTEST_TEST(Algorithms_Card_HandType, deduceHandType_straight_flush) // NOLINT
{
    EXPECT_EQ(th::HandType::deduceHandType({
                  th::HandType_Test::HEART_A,
                  th::HandType_Test::HEART_2,
                  th::HandType_Test::HEART_5,
                  th::HandType_Test::HEART_4,
                  th::HandType_Test::HEART_3,
              }),
              th::PokerHandType::StraightFlush);
}

GTEST_TEST(Algorithms_Card_HandType, isFlush_true) // NOLINT
{
    EXPECT_TRUE(th::HandType::isFlush({
        th::HandType_Test::HEART_A,
        th::HandType_Test::HEART_2,
        th::HandType_Test::HEART_3,
        th::HandType_Test::HEART_4,
        th::HandType_Test::HEART_6,
    }));
}

GTEST_TEST(Algorithms_Card_HandType, isFlush_false) // NOLINT
{
    EXPECT_FALSE(th::HandType::isFlush({
        th::HandType_Test::DIAMOND_A,
        th::HandType_Test::HEART_2,
        th::HandType_Test::HEART_3,
        th::HandType_Test::HEART_4,
        th::HandType_Test::HEART_5,
    }));
}

GTEST_TEST(Algorithms_Card_HandType, isStraight_a2345) // NOLINT
{
    EXPECT_TRUE(th::HandType::isStraight({
        th::HandType_Test::HEART_4,
        th::HandType_Test::HEART_2,
        th::HandType_Test::HEART_3,
        th::HandType_Test::HEART_A,
        th::HandType_Test::HEART_5,
    }));
}

GTEST_TEST(Algorithms_Card_HandType, isStraight_normal) // NOLINT
{
    EXPECT_TRUE(th::HandType::isStraight({
        th::HandType_Test::HEART_2,
        th::HandType_Test::HEART_5,
        th::HandType_Test::HEART_3,
        th::HandType_Test::HEART_4,
        th::HandType_Test::HEART_6,
    }));
}

GTEST_TEST(Algorithms_Card_HandType, isStraight_false) // NOLINT
{
    EXPECT_FALSE(th::HandType::isStraight({
        th::HandType_Test::HEART_A,
        th::HandType_Test::HEART_2,
        th::HandType_Test::HEART_3,
        th::HandType_Test::HEART_4,
        th::HandType_Test::HEART_6,
    }));
}

GTEST_TEST(Algorithms_Card_HandType, isFourOfAKind_true) // NOLINT
{
    EXPECT_TRUE(th::HandType::isFourOfAKind({
        std::make_pair(2, 4),
        std::make_pair(3, 1),
    }));
}

GTEST_TEST(Algorithms_Card_HandType, isFourOfAKind_false) // NOLINT
{
    EXPECT_FALSE(th::HandType::isFourOfAKind({
        std::make_pair(2, 3),
        std::make_pair(3, 1),
        std::make_pair(4, 1),
    }));
}

GTEST_TEST(Algorithms_Card_HandType, isThreeOfAKind_true) // NOLINT
{
    EXPECT_TRUE(th::HandType::isThreeOfKind({
        std::make_pair(2, 3),
        std::make_pair(3, 1),
        std::make_pair(4, 1),
    }));
}

GTEST_TEST(Algorithms_Card_HandType, isThreeOfAKind_false) // NOLINT
{
    EXPECT_FALSE(th::HandType::isThreeOfKind({
        std::make_pair(2, 2),
        std::make_pair(3, 2),
        std::make_pair(4, 1),
    }));
}

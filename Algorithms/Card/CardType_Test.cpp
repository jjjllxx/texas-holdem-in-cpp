#include <gtest/gtest.h>
#include <sys/_types/_int32_t.h>
#include <unordered_map>
#include <utility>

#include "CardType.h"
#include "Entity/Card/PokerCard.h"

namespace th
{
namespace CardType_Test
{
    const th::PokerCard HEART_A(th::CardSuit::Heart, 14);
    const th::PokerCard HEART_2(th::CardSuit::Heart, 2);
    const th::PokerCard HEART_3(th::CardSuit::Heart, 3);
    const th::PokerCard HEART_4(th::CardSuit::Heart, 4);
    const th::PokerCard HEART_5(th::CardSuit::Heart, 5);
    const th::PokerCard HEART_6(th::CardSuit::Heart, 6);
    const th::PokerCard DIAMOND_A(th::CardSuit::Diamond, 14);
    const th::PokerCard CLUB_A(th::CardSuit::Club, 14);
    const th::PokerCard SPADE_A(th::CardSuit::Spade, 14);

} // namespace CardType_Test
} // namespace th

GTEST_TEST(Algorithms_Card_CardType, isFlush_true) // NOLINT
{
    EXPECT_TRUE(th::CardType::isFlush({
        th::CardType_Test::HEART_A,
        th::CardType_Test::HEART_2,
        th::CardType_Test::HEART_3,
        th::CardType_Test::HEART_4,
        th::CardType_Test::HEART_5,
    }));
}

GTEST_TEST(Algorithms_Card_CardType, isFlush_false) // NOLINT
{
    EXPECT_FALSE(th::CardType::isFlush({
        th::CardType_Test::DIAMOND_A,
        th::CardType_Test::HEART_2,
        th::CardType_Test::HEART_3,
        th::CardType_Test::HEART_4,
        th::CardType_Test::HEART_5,
    }));
}

GTEST_TEST(Algorithms_Card_CardType, isStraight_a2345) // NOLINT
{
    EXPECT_TRUE(th::CardType::isStraight({
        th::CardType_Test::HEART_4,
        th::CardType_Test::HEART_2,
        th::CardType_Test::HEART_3,
        th::CardType_Test::HEART_A,
        th::CardType_Test::HEART_5,
    }));
}

GTEST_TEST(Algorithms_Card_CardType, isStraight_normal) // NOLINT
{
    EXPECT_TRUE(th::CardType::isStraight({
        th::CardType_Test::HEART_2,
        th::CardType_Test::HEART_5,
        th::CardType_Test::HEART_3,
        th::CardType_Test::HEART_4,
        th::CardType_Test::HEART_6,
    }));
}

GTEST_TEST(Algorithms_Card_CardType, isStraight_false) // NOLINT
{
    EXPECT_FALSE(th::CardType::isStraight({
        th::CardType_Test::HEART_A,
        th::CardType_Test::HEART_2,
        th::CardType_Test::HEART_3,
        th::CardType_Test::HEART_4,
        th::CardType_Test::HEART_6,
    }));
}

GTEST_TEST(Algorithms_Card_CardType, isFourOfAKind_true) // NOLINT
{
    EXPECT_TRUE(th::CardType::isFourOfAKind({ std::make_pair(2, 4),
                                              std::make_pair(3, 1) }));
}

GTEST_TEST(Algorithms_Card_CardType, isFourOfAKind_false) // NOLINT
{
    EXPECT_FALSE(th::CardType::isFourOfAKind({ std::make_pair(2, 3),
                                               std::make_pair(3, 1),
                                               std::make_pair(4, 1) }));
}

GTEST_TEST(Algorithms_Card_CardType, isThreeOfAKind_true) // NOLINT
{
    EXPECT_TRUE(th::CardType::isThreeOfKind({ std::make_pair(2, 3),
                                              std::make_pair(3, 1),
                                              std::make_pair(4, 1) }));
}

GTEST_TEST(Algorithms_Card_CardType, isThreeOfAKind_false) // NOLINT
{
    std::unordered_map<int32_t, int32_t> mp;
    mp[2] = 2;
    mp[3] = 2;
    mp[4] = 1;

    EXPECT_FALSE(th::CardType::isThreeOfKind({ std::make_pair(2, 2),
                                               std::make_pair(3, 2),
                                               std::make_pair(4, 1) }));
}
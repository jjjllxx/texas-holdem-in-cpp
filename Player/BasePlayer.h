#pragma once

#include "../Entity/Card/PokerCard.h"
#include "../Entity/Chip/Chip.h"

#include <stdint.h>
#include <vector>

namespace th
{
enum class PlayerAction
{
    INVALID,

    AllIn,
    Call,
    Check,
    Fold,
    PutBigBlind,
    PutSmallBlind,
    Raise,
    ReadyToStart
};

class BasePlayer
{
public:
    BasePlayer(const int32_t id);
    ~BasePlayer() = default;

    virtual void init(const th::chip& chipNum) = 0;

    void putBigBlindChip(const th::chip& bigBlindChip);
    void putSmallBlindChip(const th::chip& smallBlindChip);

    void receiveFirstCard(const th::PokerCard& firstCard);
    void receiveSecondCard(const th::PokerCard& secondCard);

    virtual th::chip takeAction(const th::chip& currBet) = 0;
    th::chip         pushChipToPool();

    void receiveChip(const th::chip& chipNum);
    void resetAfterGame();

    int32_t                    getId() const;
    th::chip                   checkChip() const;
    th::chip                   checkChipInFront() const;
    th::PlayerAction           checkLastAction() const;
    std::vector<th::PokerCard> checkHandCards() const;

    void showStatus() const;
    void peekHandCards() const;

protected:
    int32_t     id;
    std::string name;

    th::chip chip;
    th::chip chipInFront;

    std::vector<th::PokerCard> twoHandCards;

    bool hasAllIn;
    bool hasGivenUpCurrGame;

    th::PlayerAction lastAct;

    th::chip         call(const th::chip& currBet);
    th::chip         check();
    th::chip         allIn();
    th::chip         fold();
    virtual th::chip raise(const th::chip& currBet) = 0;

    void putChipInFront(const th::chip& chipNum);
    void setAction(const th::PlayerAction action);
    void printAction();
};
} // namespace th
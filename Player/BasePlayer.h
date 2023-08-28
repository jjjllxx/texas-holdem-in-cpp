#pragma once

#include "Entity/Card/PokerCard.h"
#include "Entity/Chip/Chip.h"

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

    virtual void takeAction(const th::chip& currBet) = 0;

    th::chip pushChipToPool();
    void     receiveChip(const th::chip& chipNum);
    void     resetAfterGame();

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

    th::PlayerAction           lastAct;
    std::vector<th::PokerCard> twoHandCards;

    void         call(const th::chip& currBet);
    void         check();
    void         allIn();
    void         fold();
    virtual void raise(const th::chip& currBet) = 0;

    bool needToAct() const;
    void putChipInFront(const th::chip& chipNum);
    void setAction(const th::PlayerAction action);
    void printAction() const;
};
} // namespace th
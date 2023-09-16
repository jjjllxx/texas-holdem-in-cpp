#pragma once

#include "Entity/Card/PokerCard.h"
#include "Entity/Chip/Chip.h"

#include <string>
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
    virtual ~BasePlayer() = default;

    virtual void init(const th::chip& chipNum) = 0;
    virtual void takeAction(const th::chip& curBet) = 0;

    void putBigBlindChip(const th::chip& bigBlindChip);
    void putSmallBlindChip(const th::chip& smallBlindChip);
    void receiveFirstCard(const th::PokerCard& firstCard);
    void receiveSecondCard(const th::PokerCard& secondCard);
    void receiveChip(const th::chip& chipNum);
    void prepareForNextGame();

    th::chip pushChipToPool();

    int32_t                    getId() const;
    th::chip                   checkChip() const;
    th::chip                   checkChipInFront() const;
    th::chip                   checkChipForCurGame() const;
    th::PlayerAction           checkLastAction() const;
    std::vector<th::PokerCard> checkHandCards() const;

protected:
    int32_t     id;
    std::string name;

    th::chip chip;
    th::chip chipInFront;
    th::chip chipForCurGame;

    th::PlayerAction           lastAct;
    std::vector<th::PokerCard> twoHandCards;

    void         call(const th::chip& curBet);
    void         allIn();
    virtual void raise(const th::chip& curBet) = 0;

    void putChipInFront(const th::chip& chipNum);
    void setAction(const th::PlayerAction action);
};
} // namespace th
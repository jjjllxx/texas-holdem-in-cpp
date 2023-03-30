#pragma once

#include "../Card/PokerCard.h"

#include <stdint.h>
#include <vector>

namespace th
{
class BasePlayer
{
public:
    BasePlayer(const int32_t id);
    ~BasePlayer() = default;

    virtual void init(const int32_t chipNum) = 0;

    void putBigBlindChip(const int32_t bigBlindChip);
    void putSmallBlindChip(const int32_t smallBlindChip);

    void receiveFirstCard(const th::PokerCard& firstCard);
    void receiveSecondCard(const th::PokerCard& secondCard);

    virtual int32_t takeAction(const int32_t currBet) = 0;
    int32_t         pushChipsToPool();

    bool shouldAct() const;
    void resetAfterGame();

    int32_t                    getId() const;
    int32_t                    checkChip() const;
    int32_t                    checkChipInFront() const;
    std::vector<th::PokerCard> checkHandCards() const;

    void showStatus() const;
    void peekHandCards() const;

protected:
    int32_t id;
    std::string name;

    int32_t chip;
    int32_t chipInFront;

    std::vector<th::PokerCard> twoHandCards;

    bool hasAllIn;
    bool hasGivenUpCurrGame;

    int32_t         call(const int32_t currBet);
    int32_t         allIn();
    int32_t         fold();
    virtual int32_t raise(const int32_t currBet) = 0;

    void addChip(const int32_t chipNum);
    void putChipInFront(const int32_t chipNum);
    void printAction(const int32_t      chipNum,
                     const std::string& actionName);
};
} // namespace th
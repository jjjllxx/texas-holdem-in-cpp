#pragma once

#include "../Entity/Chip/Chip.h"
#include "../Entity/Card/PokerCard.h"

#include <stdint.h>
#include <vector>

namespace th
{

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

    bool shouldAct() const;
    void resetAfterGame();

    int32_t                    getId() const;
    th::chip                   checkChip() const;
    th::chip                   checkChipInFront() const;
    std::vector<th::PokerCard> checkHandCards() const;

    void showStatus() const;
    void peekHandCards() const;

protected:
    int32_t id;
    std::string name;

    th::chip chip;
    th::chip chipInFront;

    std::vector<th::PokerCard> twoHandCards;

    bool hasAllIn;
    bool hasGivenUpCurrGame;

    th::chip         call(const th::chip& currBet);
    th::chip         allIn();
    th::chip         fold();
    virtual th::chip raise(const th::chip& currBet) = 0;

    void addChip(const th::chip& chipNum);
    void putChipInFront(const th::chip& chipNum);
    void printAction(const th::chip&    chipNum,
                     const std::string& actionName);
};
} // namespace th
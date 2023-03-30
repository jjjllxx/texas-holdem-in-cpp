#pragma once

#include "../Card/PokerCard.h"
#include "../Chip/Chip.h"

#include <stdint.h>
#include <vector>

namespace th
{

class BasePlayer
{
public:
    BasePlayer(const int32_t id);
    ~BasePlayer() = default;

    virtual void init(const th::Chip& chipNum) = 0;

    void putBigBlindChip(const th::Chip& bigBlindChip);
    void putSmallBlindChip(const th::Chip& smallBlindChip);

    void receiveFirstCard(const th::PokerCard& firstCard);
    void receiveSecondCard(const th::PokerCard& secondCard);

    virtual th::Chip takeAction(const th::Chip& currBet) = 0;
    th::Chip         pushChipToPool();

    bool shouldAct() const;
    void resetAfterGame();

    int32_t                    getId() const;
    th::Chip                   checkChip() const;
    th::Chip                   checkChipInFront() const;
    std::vector<th::PokerCard> checkHandCards() const;

    void showStatus() const;
    void peekHandCards() const;

protected:
    int32_t id;
    std::string name;

    th::Chip chip;
    th::Chip chipInFront;

    std::vector<th::PokerCard> twoHandCards;

    bool hasAllIn;
    bool hasGivenUpCurrGame;

    th::Chip         call(const th::Chip& currBet);
    th::Chip         allIn();
    th::Chip         fold();
    virtual th::Chip raise(const th::Chip& currBet) = 0;

    void addChip(const th::Chip& chipNum);
    void putChipInFront(const th::Chip& chipNum);
    void printAction(const th::Chip&    chipNum,
                     const std::string& actionName);
};
} // namespace th
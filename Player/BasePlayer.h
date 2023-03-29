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

    void init(const int32_t chipNum);

    void receiveFirstCard(const th::PokerCard& firstCard);
    void receiveSecondCard(const th::PokerCard& secondCard);

    virtual int32_t takeAction(const int32_t currBet) = 0;
    int32_t         call(const int32_t currBet);
    int32_t         allIn();
    int32_t         fold();
    virtual int32_t raise(const int32_t currBet) = 0;

    bool shouldAct() const;
    void resetAfterGame();

    int32_t                    getId() const;
    int32_t                    checkChip() const;
    std::vector<th::PokerCard> checkHandCards() const;
    virtual void showStatus() const = 0;

protected:
    int32_t id;
    int32_t chip;

    std::vector<th::PokerCard> twoHandCards;

    bool hasAllIn;
    bool hasGivenUpCurrGame;

    void addChip(const int32_t chipNum);
    void minusChip(const int32_t chipNum);
};
} // namespace th
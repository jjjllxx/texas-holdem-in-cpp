#include "BasePlayer.h"

#include "Common/Logger/Logger.h"
#include "Entity/Card/PokerCard.h"
#include "Entity/Constants.h"
#include "PlayerUtilities.h"

#include <iostream>

th::BasePlayer::BasePlayer(const int32_t id) :
    id(id),
    chip(0),
    chipInFront(0),
    lastAct(th::PlayerAction::INVALID)
{
}

void th::BasePlayer::putBigBlindChip(const th::chip& bigBlindChip)
{
    th::BasePlayer::setAction(th::PlayerAction::PutBigBlind);
    th::BasePlayer::putChipInFront(bigBlindChip);
    th::PlayerUtilities::logPlayerStatus(th::PlayerAction::PutBigBlind,
                                         th::BasePlayer::checkChipInFront(),
                                         this->name);
}

void th::BasePlayer::putSmallBlindChip(const th::chip& smallBlindChip)
{
    th::BasePlayer::setAction(th::PlayerAction::PutSmallBlind);
    th::BasePlayer::putChipInFront(smallBlindChip);
    th::PlayerUtilities::logPlayerStatus(th::PlayerAction::PutSmallBlind,
                                         th::BasePlayer::checkChipInFront(),
                                         this->name);
}

void th::BasePlayer::receiveFirstCard(const th::PokerCard& firstCard)
{
    this->twoHoleCards.clear();
    this->twoHoleCards.reserve(th::STANDARD_HOLE_CARDS_SIZE);
    this->twoHoleCards.push_back(firstCard);
}

void th::BasePlayer::receiveSecondCard(const th::PokerCard& secondCard)
{
    this->twoHoleCards.push_back(secondCard);

    if (this->twoHoleCards[0].point < this->twoHoleCards[1].point)
    {
        std::swap(this->twoHoleCards[0], this->twoHoleCards[1]);
    }
}

void th::BasePlayer::receiveChip(const th::chip& chipNum)
{
    this->chip += chipNum;
}

void th::BasePlayer::putChipInFront(const th::chip& chipNum)
{
    this->chip -= chipNum;
    this->chipInFront += chipNum;
    this->chipForCurGame += chipNum;
}

bool th::BasePlayer::prepareForNextGame()
{
    if (th::BasePlayer::checkChip() == 0)
    {
        lgw("{} has no chip, will leave the game table ...", th::BasePlayer::getName());
        return false;
    }

    this->lastAct        = th::PlayerAction::ReadyToStart;
    this->chipInFront    = 0;
    this->chipForCurGame = 0;

    return true;
}

th::chip th::BasePlayer::pushChipToPool()
{
    const th::chip chip = th::BasePlayer::checkChipInFront();
    this->chipInFront   = 0;

    return chip;
}

int32_t th::BasePlayer::getId() const
{
    return this->id;
}

std::string th::BasePlayer::getName() const
{
    return this->name;
}

th::chip th::BasePlayer::checkChip() const
{
    return this->chip;
}

th::chip th::BasePlayer::checkChipInFront() const
{
    return this->chipInFront;
}

th::chip th::BasePlayer::checkChipForCurGame() const
{
    return this->chipForCurGame;
}

th::PlayerAction th::BasePlayer::checkLastAction() const
{
    return this->lastAct;
}

std::vector<th::PokerCard> th::BasePlayer::checkHandCards() const
{
    return this->twoHoleCards;
}

void th::BasePlayer::call(const th::chip& curBet)
{
    const th::chip chipToCall = curBet - th::BasePlayer::checkChipInFront();

    if (chipToCall == 0)
    {
        return th::BasePlayer::setAction(th::PlayerAction::Check);
    }

    if (chipToCall >= th::BasePlayer::checkChip())
    {
        return th::BasePlayer::allIn();
    }

    th::BasePlayer::putChipInFront(chipToCall);
    th::BasePlayer::setAction(th::PlayerAction::Call);
}

void th::BasePlayer::allIn()
{
    th::BasePlayer::putChipInFront(th::BasePlayer::checkChip());
    th::BasePlayer::setAction(th::PlayerAction::AllIn);
}

void th::BasePlayer::setAction(const th::PlayerAction action)
{
    this->lastAct = action;
}
#include "BasePlayer.h"

#include "../Algorithms/Card/CardSelector.h"
#include "../Entity/Card/PokerCard.h"

th::BasePlayer::BasePlayer(const int32_t id) :
    id(id),
    chip(0),
    chipInFront(0),
    hasAllIn(false),
    hasGivenUpCurrGame(false)
{
}

void th::BasePlayer::putBigBlindChip(const th::chip& bigBlindChip)
{
    th::BasePlayer::setAction(th::PlayerAction::PutBigBlind);
    th::BasePlayer::printAction();
    th::BasePlayer::putChipInFront(bigBlindChip);
}

void th::BasePlayer::putSmallBlindChip(const th::chip& smallBlindChip)
{
    th::BasePlayer::setAction(th::PlayerAction::PutSmallBlind);
    th::BasePlayer::printAction();
    th::BasePlayer::putChipInFront(smallBlindChip);
}

void th::BasePlayer::receiveFirstCard(const th::PokerCard& firstCard)
{
    this->twoHandCards.clear();
    this->twoHandCards.reserve(2);
    this->twoHandCards.push_back(firstCard);
}
void th::BasePlayer::receiveSecondCard(const th::PokerCard& secondCard)
{
    this->twoHandCards.push_back(secondCard);

    if (this->twoHandCards[0].point < this->twoHandCards[1].point)
    {
        std::swap(this->twoHandCards[0], this->twoHandCards[1]);
    }
}

th::chip th::BasePlayer::pushChipToPool()
{
    const th::chip chip = th::BasePlayer::checkChipInFront();
    this->chipInFront   = 0;

    return chip;
}

void th::BasePlayer::resetAfterGame()
{
    this->hasAllIn           = false;
    this->hasGivenUpCurrGame = false;
    this->lastAct            = th::PlayerAction::ReadyToStart;
}

int32_t th::BasePlayer::getId() const
{
    return this->id;
}

th::chip th::BasePlayer::checkChip() const
{
    return this->chip;
}

th::chip th::BasePlayer::checkChipInFront() const
{
    return this->chipInFront;
}

th::PlayerAction th::BasePlayer::checkLastAction() const
{
    return this->lastAct;
}

std::vector<th::PokerCard> th::BasePlayer::checkHandCards() const
{
    return this->twoHandCards;
}

void th::BasePlayer::showStatus() const
{
    std::cout << this->name << " now has " << th::BasePlayer::checkChip().val
              << " chip." << std::endl;
}

void th::BasePlayer::peekHandCards() const
{
    this->twoHandCards.empty() == true
        ? std::cout << this->name << " do not have hand cards" << std::endl
        : std::cout << this->name << " have hand cards: "
                    << this->twoHandCards.front().getSymbol() << ' '
                    << this->twoHandCards.back().getSymbol() << std::endl;
}

th::chip th::BasePlayer::call(const th::chip& currBet)
{
    const th::chip chipToCall = currBet - th::BasePlayer::checkChipInFront();

    if (chipToCall == 0)
    {
        return th::BasePlayer::check();
    }

    if (chipToCall >= th::BasePlayer::checkChip())
    {
        return th::BasePlayer::allIn();
    }

    th::BasePlayer::putChipInFront(chipToCall);
    th::BasePlayer::setAction(th::PlayerAction::Call);
    th::BasePlayer::printAction();

    return chipToCall;
}

th::chip th::BasePlayer::check()
{
    th::BasePlayer::setAction(th::PlayerAction::Check);
    th::BasePlayer::printAction();
    return 0;
}

th::chip th::BasePlayer::fold()
{
    this->hasGivenUpCurrGame = true;
    th::BasePlayer::setAction(th::PlayerAction::Fold);
    th::BasePlayer::printAction();

    return 0;
}

th::chip th::BasePlayer::allIn()
{
    const th::chip chipLeft = th::BasePlayer::checkChip();

    this->hasAllIn = true;
    th::BasePlayer::putChipInFront(chipLeft);
    th::BasePlayer::setAction(th::PlayerAction::AllIn);
    th::BasePlayer::printAction();

    return chipLeft;
}

void th::BasePlayer::receiveChip(const th::chip& chipNum)
{
    this->chip += chipNum;
}

void th::BasePlayer::putChipInFront(const th::chip& chipNum)
{
    this->chip -= chipNum;
    this->chipInFront += chipNum;
}

void th::BasePlayer::setAction(const th::PlayerAction action)
{
    this->lastAct = action;
}

void th::BasePlayer::printAction()
{
    const th::PlayerAction action = th::BasePlayer::checkLastAction();

    std::string actionName;
    switch (action)
    {
    case th::PlayerAction::AllIn:
        actionName = " all in.";
        break;
    case th::PlayerAction::Call:
        actionName = " calls. ";
        break;
    case th::PlayerAction::Check:
        actionName = " checks.";
        break;
    case th::PlayerAction::Fold:
        actionName = " folds. ";
        break;
    case th::PlayerAction::PutBigBlind:
        actionName = " puts big blind.";
        break;
    case th::PlayerAction::PutSmallBlind:
        actionName = " puts small blind.";
        break;
    case th::PlayerAction::Raise:
        actionName = " raises.";
        break;

    case th::PlayerAction::ReadyToStart:
    case th::PlayerAction::INVALID:
    default:
        return;
    }

    std::cout << this->name << actionName << " Chips in front: "
              << th::BasePlayer::checkChipInFront().val << std::endl;
}
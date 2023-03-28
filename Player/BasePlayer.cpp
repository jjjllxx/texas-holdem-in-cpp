#include "BasePlayer.h"

th::BasePlayer::BasePlayer(const int32_t id) :
    id(id),
    chip(0),
    hasAllIn(false),
    hasGivenUpCurrGame(false)
{
}

void th::BasePlayer::init(const int32_t chipNum)
{
    th::BasePlayer::addChip(chipNum);
}

void th::BasePlayer::receiveCards(const th::PokerCard& firstCard,
                                  const th::PokerCard& secondCard)
{
    this->twoHandCards.clear();
    this->twoHandCards = { firstCard, secondCard };
}

int32_t th::BasePlayer::call(const int32_t currBet)
{
    if (currBet >= th::BasePlayer::checkChip())
    {
        return th::BasePlayer::allIn();
    }

    th::BasePlayer::minusChip(currBet);

    return currBet;
}

void th::BasePlayer::fold()
{
    this->hasGivenUpCurrGame = true;
}

int32_t th::BasePlayer::allIn()
{
    const int32_t chipLeft = th::BasePlayer::checkChip();

    this->hasAllIn = true;
    th::BasePlayer::minusChip(chipLeft);

    return chipLeft;
}

bool th::BasePlayer::isAllIn() const
{
    return this->hasAllIn;
}

bool th::BasePlayer::hasGivenUp() const
{
    return this->hasGivenUpCurrGame;
}

int32_t th::BasePlayer::getId() const
{
    return this->id;
}

int32_t th::BasePlayer::checkChip() const
{
    return this->chip;
}

std::vector<th::PokerCard> th::BasePlayer::showHandCards() const
{
    return this->twoHandCards;
}

void th::BasePlayer::addChip(const int32_t chipNum)
{
    this->chip += chipNum;
}

void th::BasePlayer::minusChip(const int32_t chipNum)
{
    this->chip -= chipNum;
}
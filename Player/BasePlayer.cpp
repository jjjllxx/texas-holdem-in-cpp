#include "BasePlayer.h"

th::BasePlayer::BasePlayer(const int32_t id) :
    id(id),
    chip(0),
    hasGivenUpCurrGame(false),
    hasAllIn(false)
{
}

void th::BasePlayer::init(const int32_t initNum)
{
    this->name += std::to_string(this->id);
    th::BasePlayer::addChip(initNum);
}

int32_t th::BasePlayer::checkChip()
{
    return this->chip;
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

bool th::BasePlayer::isAllIn()
{
    return this->hasAllIn;
}

bool th::BasePlayer::hasGivenUp()
{
    return this->hasGivenUpCurrGame;
}

void th::BasePlayer::addChip(const int32_t chipNum)
{
    this->chip += chipNum;
}

void th::BasePlayer::minusChip(const int32_t chipNum)
{
    this->chip -= chipNum;
}
#include "BasePlayer.h"
#include "../Card/PokerCard.h"

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

void th::BasePlayer::putBigBlindChip(const int32_t bigBlindChip)
{
    th::BasePlayer::printAction(bigBlindChip, "put big blind");
    th::BasePlayer::minusChip(bigBlindChip);
}

void th::BasePlayer::putSmallBlindChip(const int32_t smallBlindChip)
{
    th::BasePlayer::printAction(smallBlindChip, "put small blind");
    th::BasePlayer::minusChip(smallBlindChip);
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

bool th::BasePlayer::shouldAct() const
{
    return this->hasAllIn == false && this->hasGivenUpCurrGame == false;
}
void th::BasePlayer::resetAfterGame()
{
    this->hasAllIn           = false;
    this->hasGivenUpCurrGame = false;
}

int32_t th::BasePlayer::getId() const
{
    return this->id;
}

int32_t th::BasePlayer::checkChip() const
{
    return this->chip;
}

std::vector<th::PokerCard> th::BasePlayer::checkHandCards() const
{
    return this->twoHandCards;
}

int32_t th::BasePlayer::call(const int32_t currBet)
{
    if (currBet >= th::BasePlayer::checkChip())
    {
        return th::BasePlayer::allIn();
    }

    th::BasePlayer::minusChip(currBet);
    th::BasePlayer::printAction(currBet, "call");

    return currBet;
}

int32_t th::BasePlayer::fold()
{
    this->hasGivenUpCurrGame = true;
    th::BasePlayer::printAction(0, "fold");

    return 0;
}

int32_t th::BasePlayer::allIn()
{
    const int32_t chipLeft = th::BasePlayer::checkChip();

    this->hasAllIn = true;
    th::BasePlayer::minusChip(chipLeft);
    th::BasePlayer::printAction(chipLeft, "all in");

    return chipLeft;
}

void th::BasePlayer::addChip(const int32_t chipNum)
{
    this->chip += chipNum;
}

void th::BasePlayer::minusChip(const int32_t chipNum)
{
    this->chip -= chipNum;
}

void th::BasePlayer::printAction(const int32_t      chipNum,
                                 const std::string& actionName)
{
    chipNum == 0
        ? std ::cout << "Player " << th::BasePlayer::getId() << ' ' << actionName << std::endl
        : std ::cout << "Player " << th::BasePlayer::getId() << ' ' << actionName << " with " << chipNum << std::endl;
}
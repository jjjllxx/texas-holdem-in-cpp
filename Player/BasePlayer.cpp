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

int32_t th::BasePlayer::call(const int32_t currBet)
{
    if (currBet >= th::BasePlayer::checkChip())
    {
        return th::BasePlayer::allIn();
    }

    th::BasePlayer::minusChip(currBet);

    std::cout << "Player " << th::BasePlayer::getId() << " calls. " << std::endl;

    return currBet;
}

int32_t th::BasePlayer::fold()
{
    this->hasGivenUpCurrGame = true;

    std::cout << "Player " << th::BasePlayer::getId() << " folds. " << std::endl;

    return 0;
}

int32_t th::BasePlayer::allIn()
{
    const int32_t chipLeft = th::BasePlayer::checkChip();

    this->hasAllIn = true;
    th::BasePlayer::minusChip(chipLeft);

    std::cout << "Player " << th::BasePlayer::getId() << " all in with " << chipLeft << std::endl;

    return chipLeft;
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
    // if (this->twoHandCards.empty() == true)
    // {
    //     std::cout << "Player" << th::BasePlayer::getId() << " does not have hand cards" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Player" << th::BasePlayer::getId() << "\'s hand cards: "
    //               << this->twoHandCards.front().getSymbol() << ' '
    //               << this->twoHandCards.back().getSymbol() << std::endl;
    // }

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
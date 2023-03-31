#include "BasePlayer.h"
#include "../Card/PokerCard.h"

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
    th::BasePlayer::printAction(bigBlindChip, "put big blind");
    th::BasePlayer::putChipInFront(bigBlindChip);
}

void th::BasePlayer::putSmallBlindChip(const th::chip& smallBlindChip)
{
    th::BasePlayer::printAction(smallBlindChip, "put small blind");
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

th::chip th::BasePlayer::checkChip() const
{
    return this->chip;
}

th::chip th::BasePlayer::checkChipInFront() const
{
    return this->chipInFront;
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

    if (chipToCall >= th::BasePlayer::checkChip())
    {
        return th::BasePlayer::allIn();
    }

    th::BasePlayer::putChipInFront(chipToCall);
    th::BasePlayer::printAction(chipToCall, "call");

    return chipToCall;
}

th::chip th::BasePlayer::fold()
{
    this->hasGivenUpCurrGame = true;
    th::BasePlayer::printAction(0, "fold");

    return 0;
}

th::chip th::BasePlayer::allIn()
{
    const th::chip chipLeft = th::BasePlayer::checkChip();

    this->hasAllIn = true;
    th::BasePlayer::putChipInFront(chipLeft);
    th::BasePlayer::printAction(chipLeft, "all in");

    return chipLeft;
}

void th::BasePlayer::addChip(const th::chip& chipNum)
{
    this->chip += chipNum;
}

void th::BasePlayer::putChipInFront(const th::chip& chipNum)
{
    this->chip -= chipNum;
    this->chipInFront += chipNum;
}

void th::BasePlayer::printAction(const th::chip&    chipNum,
                                 const std::string& actionName)
{
    chipNum == 0
        ? std ::cout << this->name << ' ' << actionName << ". " << std::endl
        : std ::cout << this->name << ' ' << actionName << " with " << chipNum.val << ". " << std::endl;
}
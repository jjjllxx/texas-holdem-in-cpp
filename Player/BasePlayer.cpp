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

void th::BasePlayer::putBigBlindChip(const th::Chip& bigBlindChip)
{
    th::BasePlayer::printAction(bigBlindChip, "put big blind");
    th::BasePlayer::putChipInFront(bigBlindChip);
}

void th::BasePlayer::putSmallBlindChip(const th::Chip& smallBlindChip)
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

th::Chip th::BasePlayer::pushChipToPool()
{
    const th::Chip chip = th::BasePlayer::checkChipInFront();
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

th::Chip th::BasePlayer::checkChip() const
{
    return this->chip;
}

th::Chip th::BasePlayer::checkChipInFront() const
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

th::Chip th::BasePlayer::call(const th::Chip& currBet)
{
    const th::Chip chipToCall = currBet - th::BasePlayer::checkChipInFront();

    if (chipToCall >= th::BasePlayer::checkChip())
    {
        return th::BasePlayer::allIn();
    }

    th::BasePlayer::putChipInFront(chipToCall);
    th::BasePlayer::printAction(chipToCall, "call");

    return chipToCall;
}

th::Chip th::BasePlayer::fold()
{
    this->hasGivenUpCurrGame = true;
    th::BasePlayer::printAction(0, "fold");

    return 0;
}

th::Chip th::BasePlayer::allIn()
{
    const th::Chip chipLeft = th::BasePlayer::checkChip();

    this->hasAllIn = true;
    th::BasePlayer::putChipInFront(chipLeft);
    th::BasePlayer::printAction(chipLeft, "all in");

    return chipLeft;
}

void th::BasePlayer::addChip(const th::Chip& chipNum)
{
    this->chip += chipNum;
}

void th::BasePlayer::putChipInFront(const th::Chip& chipNum)
{
    this->chip -= chipNum;
    this->chipInFront += chipNum;
}

void th::BasePlayer::printAction(const th::Chip&    chipNum,
                                 const std::string& actionName)
{
    chipNum == 0
        ? std ::cout << this->name << ' ' << actionName << ". " << std::endl
        : std ::cout << this->name << ' ' << actionName << " with " << chipNum.val << ". " << std::endl;
}
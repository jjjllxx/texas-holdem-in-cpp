#include "AutoPlayer.h"

#include "Algorithms/Random/Random.h"

th::AutoPlayer::AutoPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}

void th::AutoPlayer::init(const th::chip& chipNum)
{
    this->name = "Player " + std::to_string(th::BasePlayer::getId());
    th::AutoPlayer::receiveChip(chipNum);
}

void th::AutoPlayer::takeAction(const th::chip& curBet)
{
    if (th::AutoPlayer::needToAct() == false)
    {
        return;
    }

    const int32_t action = curBet * 5 < th::AutoPlayer::checkChip()
                               ? th::Random::generateWithin(0, 2)
                               : th::Random::generateWithin(0, 3);
    switch (action)
    {
    case (0):
        return th::AutoPlayer::fold();
    case (1):
        return th::AutoPlayer::call(curBet);
    case (2):
        return th::AutoPlayer::raise(curBet);
    case (3):
        return th::AutoPlayer::allIn();
    default:
        break;
    }
}

void th::AutoPlayer::raise(const th::chip& curBet)
{
    const th::chip raiseBet = curBet == 0
                                  ? th::chip { 25 } - th::AutoPlayer::checkChipInFront()
                                  : curBet * 2.5 - th::AutoPlayer::checkChipInFront();

    if (raiseBet >= th::AutoPlayer::checkChip())
    {
        return th::AutoPlayer::allIn();
    }

    th::AutoPlayer::putChipInFront(raiseBet);
    th::AutoPlayer::setAction(th::PlayerAction::Raise);
    th::AutoPlayer::printAction();
}
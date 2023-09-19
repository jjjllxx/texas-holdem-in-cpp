#include "AutoPlayer.h"

#include "Algorithms/Random.h"

#include "PlayerUtilities.h"

th::AutoPlayer::AutoPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}

void th::AutoPlayer::init(const th::chip& chipNum)
{
    this->name = "Player " + std::to_string(th::AutoPlayer::getId());
    th::AutoPlayer::receiveChip(chipNum);
}

void th::AutoPlayer::takeAction(const th::chip& curBet)
{
    if (th::PlayerUtilities::needToAct(this->name, th::AutoPlayer::checkLastAction()) == false)
    {
        return;
    }

    const int32_t action = curBet * 5 < th::AutoPlayer::checkChip()
                               ? th::Random::generateWithin<int32_t>(0, 2)
                               : th::Random::generateWithin<int32_t>(0, 3);
    switch (action)
    {
    case (0):
        th::BasePlayer::setAction(th::PlayerAction::Fold);
        break;
    case (1):
        th::AutoPlayer::call(curBet);
        break;
    case (2):
        th::AutoPlayer::raise(curBet);
        break;
    case (3):
        th::AutoPlayer::allIn();
        break;
    default:
        break;
    }

    th::PlayerUtilities::logPlayerStatus(th::AutoPlayer::checkLastAction(),
                                         th::AutoPlayer::checkChipInFront(),
                                         this->name);
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
}
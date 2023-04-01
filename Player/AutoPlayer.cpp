#include "AutoPlayer.h"

#include "../Algorithms/Random/Random.h"

th::AutoPlayer::AutoPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}

void th::AutoPlayer::init(const th::chip& chipNum)
{
    this->name = "Player " + std::to_string(th::BasePlayer::getId());
    th::BasePlayer::addChip(chipNum);
}

th::chip th::AutoPlayer::takeAction(const th::chip& currBet)
{
    const int32_t action = currBet * 5 < th::AutoPlayer::checkChip()
                               ? th::Random::generateWithin(0, 2)
                               : th::Random::generateWithin(0, 3);

    std::cout << action << std::endl;
    switch (action)
    {
    case (0):
        return th::AutoPlayer::fold();
    case (1):
        return th::AutoPlayer::call(currBet);
    case (2):
        return th::AutoPlayer::raise(currBet);
    case (3):
        return th::AutoPlayer::allIn();
    default:
        break;
    }

    return 0;
}

th::chip th::AutoPlayer::raise(const th::chip& currBet)
{
    const th::chip raiseBet = currBet == 0
                                  ? th::chip { 25 } - th::AutoPlayer::checkChipInFront()
                                  : currBet * 2.5 - th::AutoPlayer::checkChipInFront();

    if (raiseBet >= th::AutoPlayer::checkChip())
    {
        return th::AutoPlayer::allIn();
    }

    th::AutoPlayer::putChipInFront(raiseBet);
    th::AutoPlayer::printAction(raiseBet, "raise money");

    return raiseBet;
}
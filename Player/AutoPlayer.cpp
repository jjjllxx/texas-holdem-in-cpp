#include "AutoPlayer.h"

#include <random>

th::AutoPlayer::AutoPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}

int32_t th::AutoPlayer::takeAction(const int32_t currBet)
{
    const int32_t action = std::chrono::system_clock::now().time_since_epoch().count() % 4;

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

int32_t th::AutoPlayer::raise(const int32_t currBet)
{
    const int32_t raiseBet = currBet == 0
                                 ? 25
                                 : currBet * 2.5;

    th::BasePlayer::minusChip(raiseBet);

    std::cout << "Player " << th::AutoPlayer::getId() << " raise money to " << raiseBet << std::endl;

    return raiseBet;
}

void th::AutoPlayer::showStatus() const
{
    std::cout << "Auto player " << th::AutoPlayer::getId()
              << " now has " << th::AutoPlayer::checkChip()
              << " chips." << std::endl;
}
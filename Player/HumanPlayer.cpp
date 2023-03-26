#include "HumanPlayer.h"

th::HumanPlayer::HumanPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}

int32_t th::HumanPlayer::raise(const int32_t currBet)
{
    int32_t raiseBet = 0;
    while (raiseBet < currBet)
    {
        std::cout << "Please enter a number higher than current bet (" << currBet << ") : ";
        std::cin >> raiseBet;
    }

    if (raiseBet > th::BasePlayer::checkChip())
    {
        return th::BasePlayer::allIn();
    }

    th::BasePlayer::minusChip(raiseBet);

    return raiseBet;
}
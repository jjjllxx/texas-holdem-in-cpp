#include "AutoPlayer.h"

th::AutoPlayer::AutoPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}

int32_t th::AutoPlayer::raise(const int32_t currBet)
{
    const int32_t raiseBet = currBet * 2.5;
    th::BasePlayer::minusChip(raiseBet);

    return raiseBet;
}
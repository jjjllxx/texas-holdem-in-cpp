#pragma once

#include "PokerCard.h"

namespace th
{
    struct HandCard
    {
        HandCard();

        th::PokerCard firstHandCard;
        th::PokerCard secondHandCard;
    };
    } // namespace th
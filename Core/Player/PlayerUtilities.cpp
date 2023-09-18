#include "PlayerUtilities.h"

#include "BasePlayer.h"
#include "Entity/Chip/Chip.h"

#include <iostream>

void th::PlayerUtilities::logPlayerStatus(const th::PlayerAction lastAction,
                                          const th::chip&        chipInFront,
                                          const std::string&     name)
{
    std::string actionName;
    switch (lastAction)
    {
    case th::PlayerAction::AllIn:
        actionName = " all in.";
        break;
    case th::PlayerAction::Call:
        actionName = " calls.";
        break;
    case th::PlayerAction::Check:
        actionName = " checks.";
        break;
    case th::PlayerAction::Fold:
        actionName = " folds.";
        break;
    case th::PlayerAction::PutBigBlind:
        actionName = " puts big blind.";
        break;
    case th::PlayerAction::PutSmallBlind:
        actionName = " puts small blind.";
        break;
    case th::PlayerAction::Raise:
        actionName = " raises.";
        break;
    case th::PlayerAction::ReadyToStart:
        actionName = " is ready to start.";
        break;
    case th::PlayerAction::INVALID:
        actionName = " is in INVALID status.";
        break;
    default:
        return;
    }

    std::cout << name << actionName << " Now chips in front: "
              << chipInFront.val << std::endl;
}

bool th::PlayerUtilities::needToAct(const std::string&     name,
                                    const th::PlayerAction lastAction)
{
    if (lastAction == th::PlayerAction::Fold)
    {
        std::cout << name << " has already folded. " << std::endl;
        return false;
    }

    if (lastAction == th::PlayerAction::AllIn)
    {
        std::cout << name << " has already all in. " << std::endl;
        return false;
    }

    return true;
}
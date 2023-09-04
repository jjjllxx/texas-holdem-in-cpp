#include "HumanPlayer.h"

#include <iostream>

th::HumanPlayer::HumanPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}
void th::HumanPlayer::init(const th::chip& chipNum)
{
    this->name = "You(Player 0)";
    th::HumanPlayer::receiveChip(chipNum);
}

void th::HumanPlayer::takeAction(const th::chip& curBet)
{
    if (th::HumanPlayer::needToAct() == false)
    {
        return;
    }

    th::HumanPlayer::peekHandCards();
    th::HumanPlayer::showStatus();
    std::cout << "Current bet is " << curBet.val
              << ". Please enter a number to decide action: \n"
              << "0. Fold \n"
              << "1. Call \n"
              << "2. Raise \n"
              << "3. All In" << std::endl;

    int32_t action = 1;
    std::cin >> action;

    switch (action)
    {
    case (0):
        return th::HumanPlayer::fold();
    case (1):
        return th::HumanPlayer::call(curBet);
    case (2):
        return th::HumanPlayer::raise(curBet);
    case (3):
        return th::HumanPlayer::allIn();
    default:
        break;
    }

    return th::HumanPlayer::takeAction(curBet);
}

void th::HumanPlayer::raise(const th::chip& curBet)
{
    const th::chip neededChip = curBet - th::HumanPlayer::checkChipInFront();
    int32_t        inputVal   = 0;

    while (inputVal < neededChip.val)
    {
        std::cout << "Current bet is " << curBet.val
                  << ". You have " << th::HumanPlayer::checkChipInFront().val
                  << " in front. You need at least "
                  << neededChip.val << " to raise. Please enter: ";
        std::cin >> inputVal;
    }

    th::chip raiseBet = inputVal;

    if (raiseBet > th::HumanPlayer::checkChip())
    {
        return th::HumanPlayer::allIn();
    }

    th::HumanPlayer::putChipInFront(raiseBet);
    th::HumanPlayer::setAction(th::PlayerAction::Raise);
    th::HumanPlayer::printAction();
}
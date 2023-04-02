#include "HumanPlayer.h"

th::HumanPlayer::HumanPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}
void th::HumanPlayer::init(const th::chip& chipNum)
{
    this->name = "You(Player 0)";
    th::BasePlayer::receiveChip(chipNum);
}

th::chip th::HumanPlayer::takeAction(const th::chip& currBet)
{
    if (th::BasePlayer::needToAct() == false)
    {
        return 0;
    }

    th::HumanPlayer::peekHandCards();
    th::HumanPlayer::showStatus();
    std::cout << "Current bet is " << currBet.val
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
        return th::HumanPlayer::call(currBet);
    case (2):
        return th::HumanPlayer::raise(currBet);
    case (3):
        return th::HumanPlayer::allIn();
    default:
        break;
    }

    return th::HumanPlayer::takeAction(currBet);
}

th::chip th::HumanPlayer::raise(const th::chip& currBet)
{
    const th::chip neededChip = currBet - th::HumanPlayer::checkChipInFront();
    int32_t        inputVal   = 0;

    while (inputVal < neededChip.val)
    {
        std::cout << "Current bet is " << currBet.val
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

    return raiseBet;
}
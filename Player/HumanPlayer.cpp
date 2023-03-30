#include "HumanPlayer.h"

th::HumanPlayer::HumanPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}
void th::HumanPlayer::init(const int32_t chipNum)
{
    this->name = "You(Player 0)";
    th::BasePlayer::addChip(chipNum);
}

int32_t th::HumanPlayer::takeAction(const int32_t currBet)
{
    th::HumanPlayer::peekHandCards();
    th::HumanPlayer::showStatus();
    std::cout << "Current bet is " << currBet
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

int32_t th::HumanPlayer::raise(const int32_t currBet)
{
    const int32_t neededChips = currBet - th::HumanPlayer::checkChipInFront();
    int32_t       raiseBet    = 0;

    while (raiseBet < neededChips)
    {
        std::cout << "Current bet is " << currBet
                  << ". You have " << th::HumanPlayer::checkChipInFront()
                  << " in front. You need at least "
                  << neededChips << " to raise. Please enter: ";
        std::cin >> raiseBet;
    }

    if (raiseBet > th::HumanPlayer::checkChip())
    {
        return th::HumanPlayer::allIn();
    }

    th::HumanPlayer::putChipInFront(raiseBet);
    th::HumanPlayer::printAction(raiseBet, "raise money");

    return raiseBet;
}
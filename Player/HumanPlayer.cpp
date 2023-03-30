#include "HumanPlayer.h"

th::HumanPlayer::HumanPlayer(const int32_t id) :
    th::BasePlayer(id)
{
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
    int32_t raiseBet = 0;
    while (raiseBet < currBet)
    {
        std::cout << "Please enter a number higher than current bet (" << currBet << ") : ";
        std::cin >> raiseBet;
    }

    if (raiseBet > th::HumanPlayer::checkChip())
    {
        return th::HumanPlayer::allIn();
    }

    th::HumanPlayer::minusChip(raiseBet);
    th::HumanPlayer::printAction(raiseBet, "raise money");

    return raiseBet;
}

void th::HumanPlayer::showStatus() const
{
    std::cout << "Human player(you) " << th::HumanPlayer::getId()
              << " now has " << th::HumanPlayer::checkChip()
              << " chips." << std::endl;
}

void th::HumanPlayer::peekHandCards() const
{
    this->twoHandCards.empty() == true
        ? std::cout << "You do not have hand cards" << std::endl
        : std::cout << "You have hand cards: "
                    << this->twoHandCards.front().getSymbol() << ' '
                    << this->twoHandCards.back().getSymbol() << std::endl;
}
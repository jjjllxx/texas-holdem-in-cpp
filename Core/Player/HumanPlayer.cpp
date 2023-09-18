#include "HumanPlayer.h"

#include "Common/Logger/Logger.h"
#include "PlayerUtilities.h"

#include <iostream>

th::HumanPlayer::HumanPlayer(const int32_t id) :
    th::BasePlayer(id)
{
}
void th::HumanPlayer::init(const th::chip& chipNum)
{
    this->name = "Player 0 (You)";
    th::HumanPlayer::receiveChip(chipNum);
}

void th::HumanPlayer::takeAction(const th::chip& curBet)
{
    if (th::PlayerUtilities::needToAct(this->name, th::HumanPlayer::checkLastAction()) == false)
    {
        return;
    }

    th::HumanPlayer::peekHandCards();
    th::HumanPlayer::showStatus();
    std::cout << "Current bet is " << curBet.val
              << ". Please enter a number to act: \n"
              << "0. Fold \n"
              << "1. Call \n"
              << "2. Raise \n"
              << "3. All In" << std::endl;

    int32_t action = 1;
    std::cin >> action;

    switch (action)
    {
    case (0):
        th::BasePlayer::setAction(th::PlayerAction::Fold);
        break;
    case (1):
        th::HumanPlayer::call(curBet);
        break;
    case (2):
        th::HumanPlayer::raise(curBet);
        break;
    case (3):
        th::HumanPlayer::allIn();
        break;
    default:
        lgw("Invalid action! Please select a correct number!");
        return th::HumanPlayer::takeAction(curBet);
    }

    th::PlayerUtilities::logPlayerStatus(th::HumanPlayer::checkLastAction(),
                                         th::HumanPlayer::checkChipInFront(),
                                         this->name);
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
}

void th::HumanPlayer::showStatus() const
{
    std::cout << this->name << " now has " << th::BasePlayer::checkChip().val
              << " chip." << std::endl;
}

void th::HumanPlayer::peekHandCards() const
{
    this->twoHoleCards.empty() == true
        ? std::cout << this->name << " do not have hand cards" << std::endl
        : std::cout << this->name << " have hand cards: "
                    << th::PokerCardUtility::toSymbol(this->twoHoleCards.front()) << ' '
                    << th::PokerCardUtility::toSymbol(this->twoHoleCards.back()) << std::endl;
}
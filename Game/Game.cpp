#include "Game.h"
#include "Game/ChipAllocation.h"
#include "GameSettlement.h"

#include "Entity/Card/CardDeck.h"
#include "Entity/Card/PokerCard.h"
#include "Entity/Chip/Chip.h"
#include "Player/BasePlayer.h"
#include "Utilities/Constants.h"

#include <iostream>

bool th::Game::initGame(const std::size_t playerNum,
                        const std::size_t smallBlindPos,
                        const th::chip&   smallBlindChip)
{
    if (smallBlindChip <= 0)
    {
        return false;
    }

    this->smallBlindPos     = smallBlindPos;
    this->smallBlindChip    = smallBlindChip;
    this->survivedPlayerNum = playerNum;

    return true;
}

void th::Game::startGame(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::handleBlinds(players);
    th::Game::dealCards(cardDeck, players);
    th::Game::oneRound(0, th::PREFLOP_ROUND, cardDeck, players);
    th::Game::oneRound(3, th::FLOP_ROUND, cardDeck, players);
    th::Game::oneRound(1, th::TURN_ROUND, cardDeck, players);
    th::Game::oneRound(1, th::RIVER_ROUND, cardDeck, players);

    std::vector<std::shared_ptr<th::BasePlayer>> winners
        = th::GameSettlement::decideWinners(this->publicCards, players);
    th::ChipAllocation::allocateChip(winners, players);
}

void th::Game::handleBlinds(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus("Handling blinds...");

    players[this->smallBlindPos]->putSmallBlindChip(this->smallBlindChip);
    const std::size_t bigBlindPos = (this->smallBlindPos + 1) % players.size();
    players[bigBlindPos]->putBigBlindChip(this->smallBlindChip * 2);
    this->curPool += this->smallBlindChip * 3;
}

void th::Game::dealCards(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus("Dealing Cards...");
    cardDeck.shuffle();
    const std::size_t playerNum = players.size();

    for (std::size_t i = 0; i < playerNum; ++i)
    {
        const std::size_t pos = (i + this->smallBlindPos) % playerNum;
        players[pos]->receiveFirstCard(cardDeck.getCurTop());
    }

    for (std::size_t i = 0; i < playerNum; ++i)
    {
        const std::size_t pos = (i + this->smallBlindPos) % playerNum;
        players[pos]->receiveSecondCard(cardDeck.getCurTop());
    }
}

void th::Game::oneRound(const std::size_t                             cardNumToReveal,
                        const std::string&                            roundName,
                        th::CardDeck&                                 cardDeck,
                        std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus(roundName);
    th::Game::revealPublicCards(cardNumToReveal, cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::playersTakeAction(players);
    th::Game::collectChips(players);
}

void th::Game::logGameStatus(const std::string& status) const
{
    std::cout << status << " starts. Now pool is " << this->curPool.val << std::endl;
}

void th::Game::revealPublicCards(const std::size_t cardNumToReveal,
                                 th::CardDeck&     cardDeck)
{
    for (std::size_t i = 0; i < cardNumToReveal; ++i)
    {
        this->publicCards.push_back(cardDeck.getCurTopNext());
    }
}

void th::Game::showCurrPublicCards() const
{
    if (this->publicCards.empty() == true)
    {
        std::cout << "Currently No Public Cards!";
    }

    for (const th::PokerCard& card : this->publicCards)
    {
        std::cout << th::PokerCardUtility::toSymbol(card) << ' ';
    }

    std::cout << std::endl;
}

void th::Game::playersTakeAction(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    const std::size_t playerNum = players.size();
    const bool        isPreflop = this->publicCards.empty() == true;

    std::size_t curAt  = isPreflop == true
                             ? (this->smallBlindPos + 2) % playerNum
                             : this->smallBlindPos;
    th::chip    curBet = isPreflop == true
                             ? this->smallBlindChip * 2
                             : 0;

    std::size_t shouldEndAt = curAt;

    while (true)
    {
        const th::PlayerAction prevAct = players[curAt]->checkLastAction();

        players[curAt]->takeAction(curBet);

        if (const th::chip curChipInFront = players[curAt]->checkChipInFront();
            curChipInFront > curBet)
        {
            shouldEndAt = curAt;
            curBet      = curChipInFront;
        }

        if (const th::PlayerAction curAct = players[curAt]->checkLastAction();
            curAct == th::PlayerAction::Fold && curAct != prevAct)
        {
            this->survivedPlayerNum--;
            if (this->survivedPlayerNum == 1)
            {
                break;
            }
        }

        ++curAt;
        curAt %= playerNum;

        if (curAt == shouldEndAt)
        {
            break;
        }
    }
}

void th::Game::collectChips(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        this->curPool += player->pushChipToPool();
    }
}
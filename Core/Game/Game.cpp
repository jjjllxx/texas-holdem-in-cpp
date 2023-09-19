#include "Game.h"
#include "ChipAllocation.h"
#include "GameSettlement.h"

#include "Common/Logger/Logger.h"
#include "Core/Player/BasePlayer.h"
#include "Entity/Card/CardDeck.h"
#include "Entity/Card/PokerCard.h"
#include "Entity/Chip/Chip.h"
#include "Entity/Constants.h"

#include <iostream>

bool th::Game::initGame(const std::size_t playersCnt,
                        const std::size_t smallBlindPos,
                        const th::chip&   smallBlindChip)
{
    if (smallBlindChip <= 0)
    {
        return false;
    }

    this->smallBlindPos    = smallBlindPos;
    this->smallBlindChip   = smallBlindChip;
    this->allInPlayersCnt  = 0;
    this->unfoldPlayersCnt = playersCnt;
    this->communityCards.reserve(th::STANDARD_COMMUNITY_CARDS_SIZE);

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
        = th::GameSettlement::decideWinners(this->communityCards, players);
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
    const std::size_t playersCnt = players.size();

    for (std::size_t i = 0; i < playersCnt; ++i)
    {
        const std::size_t pos = (i + this->smallBlindPos) % playersCnt;
        players[pos]->receiveFirstCard(cardDeck.getCurTop());
    }

    for (std::size_t i = 0; i < playersCnt; ++i)
    {
        const std::size_t pos = (i + this->smallBlindPos) % playersCnt;
        players[pos]->receiveSecondCard(cardDeck.getCurTop());
    }
}

void th::Game::oneRound(const std::size_t                             cardNumToReveal,
                        const std::string&                            roundName,
                        th::CardDeck&                                 cardDeck,
                        std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    if (this->unfoldPlayersCnt == 1)
    {
        lgi("Only 1 player left, skip {} ..", roundName);
        return;
    }

    
    th::Game::revealPublicCards(cardNumToReveal, cardDeck);
    th::Game::showCurrPublicCards();

    if (this->unfoldPlayersCnt == this->allInPlayersCnt)
    {
        lgi("All left players all-in, skip player action part");
        return;
    }

    th::Game::playersTakeAction(players);
    th::Game::collectChips(players);
}

void th::Game::logGameStatus(const std::string& status) const
{
    lgi("{} starts. Now pool is {}", status, this->curPool.val);
}

void th::Game::revealPublicCards(const std::size_t cardNumToReveal,
                                 th::CardDeck&     cardDeck)
{
    for (std::size_t i = 0; i < cardNumToReveal; ++i)
    {
        this->communityCards.push_back(cardDeck.getCurTopNext());
    }
}

void th::Game::showCurrPublicCards() const
{
    if (this->communityCards.empty() == true)
    {
        std::cout << "Currently No Public Cards!";
    }

    for (const th::PokerCard& card : this->communityCards)
    {
        std::cout << th::PokerCardUtility::toSymbol(card) << ' ';
    }

    std::cout << std::endl;
}

void th::Game::playersTakeAction(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    const std::size_t playersCnt = players.size();
    const bool        isPreflop  = this->communityCards.empty() == true;

    std::size_t curAt  = isPreflop == true
                             ? (this->smallBlindPos + 2) % playersCnt
                             : this->smallBlindPos;
    th::chip    curBet = isPreflop == true
                             ? this->smallBlindChip * 2
                             : 0;

    std::size_t shouldEndAt = curAt;

    while (true)
    {
        std::shared_ptr<th::BasePlayer>& curPlayer = players[curAt];
        const th::PlayerAction           prevAct   = curPlayer->checkLastAction();

        curPlayer->takeAction(curBet);

        if (const th::chip curChipInFront = curPlayer->checkChipInFront();
            curChipInFront > curBet)
        {
            shouldEndAt = curAt;
            curBet      = curChipInFront;
        }

        if (const th::PlayerAction curAct = curPlayer->checkLastAction();
            curAct != prevAct)
        {
            if (curAct == th::PlayerAction::Fold)
            {
                this->unfoldPlayersCnt--;
            }

            if (curAct == th::PlayerAction::AllIn)
            {
                this->allInPlayersCnt++;
            }

            if (this->unfoldPlayersCnt == 1)
            {
                return;
            }
        }

        ++curAt;
        curAt %= playersCnt;

        if (curAt == shouldEndAt)
        {
            return;
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
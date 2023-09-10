#include "Game.h"

#include "Entity/Card/CardDeck.h"
#include "Entity/Card/PokerCard.h"
#include "Entity/Chip/Chip.h"
#include "Player/BasePlayer.h"

#include <iostream>

bool th::Game::initGame(const std::size_t smallBlindPos,
                        const th::chip&   smallBlindChip)
{
    if (smallBlindChip <= 0)
    {
        return false;
    }

    this->smallBlindPos  = smallBlindPos;
    this->smallBlindChip = smallBlindChip;

    return true;
}

void th::Game::startGame(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::handleBlinds(players);
    th::Game::dealCards(cardDeck, players);
    th::Game::oneRound(0, "Preflop Round", cardDeck, players);
    th::Game::oneRound(3, "Flop Round", cardDeck, players);
    th::Game::oneRound(1, "Turn Round", cardDeck, players);
    th::Game::oneRound(1, "River Round", cardDeck, players);
}

void th::Game::handleBlinds(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    players[this->smallBlindPos]->putSmallBlindChip(this->smallBlindChip);
    const std::size_t bigBlindPos = (this->smallBlindPos + 1) % players.size();
    players[bigBlindPos]->putBigBlindChip(this->smallBlindChip * 2);
    this->curPool += this->smallBlindChip * 3;
}

void th::Game::dealCards(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus("Dealing Cards...");
    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        player->receiveFirstCard(cardDeck.getCurrTop());
    }

    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        player->receiveSecondCard(cardDeck.getCurrTop());
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
        this->publicCards.push_back(cardDeck.getCurrTopNext());
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
        if (prevAct == th::PlayerAction::Fold)
        {
            ++curAt;
            curAt %= playerNum;
            continue;
        }

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
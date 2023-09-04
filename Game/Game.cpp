#include "Game.h"

#include "Entity/Card/CardDeck.h"
#include "Entity/Card/PokerCard.h"
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
    th::Game::preflopRound(players);
    th::Game::flopRound(cardDeck, players);
    th::Game::turnRound(cardDeck, players);
    th::Game::riverRound(cardDeck, players);
}

void th::Game::handleBlinds(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::putSmallBlind(this->smallBlindChip, players[this->smallBlindPos]);
    const std::size_t bigBlindPos = (this->smallBlindPos + 1) % players.size();
    th::Game::putBigBlind(this->smallBlindChip * 2, players[bigBlindPos]);
}

void th::Game::dealCards(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus("Dealing cards");
    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        player->receiveFirstCard(cardDeck.getCurrTop());
    }

    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        player->receiveSecondCard(cardDeck.getCurrTop());
    }
}

void th::Game::preflopRound(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus("Preflop Round");
    th::Game::oneRound(this->smallBlindPos + 2, players);
    th::Game::collectChip(players);
}

void th::Game::flopRound(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus("Flop Round");
    th::Game::updateCurrBet(0);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
    th::Game::collectChip(players);
}

void th::Game::turnRound(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus("Turn Round");
    th::Game::updateCurrBet(0);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
    th::Game::collectChip(players);
}

void th::Game::riverRound(th::CardDeck&                                 cardDeck,
                          std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::logGameStatus("River Round");
    th::Game::updateCurrBet(0);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
    th::Game::collectChip(players);
}

void th::Game::putBigBlind(const th::chip&                  bigBlindChip,
                           std::shared_ptr<th::BasePlayer>& bigBlindPlayer)
{
    bigBlindPlayer->putBigBlindChip(bigBlindChip);
    th::Game::updateCurrBet(bigBlindChip);
    th::Game::addToPool(bigBlindChip);
}
void th::Game::putSmallBlind(const th::chip&                  smallBlindChip,
                             std::shared_ptr<th::BasePlayer>& smallBlindPlayer)
{
    smallBlindPlayer->putSmallBlindChip(smallBlindChip);
    th::Game::addToPool(smallBlindChip);
}

void th::Game::collectChip(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        const th::chip chipInFront = player->pushChipToPool();
        th::Game::addToPool(chipInFront);
        chipsMap.insert_or_assign(player->getId(), chipInFront);
    }
}

void th::Game::revealOnePublicCard(th::CardDeck& cardDeck)
{
    this->publicCards.push_back(cardDeck.getCurrTopNext());
}

void th::Game::oneRound(const std::size_t                             startAt,
                        std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    const std::size_t playerNum = players.size();

    std::size_t curAt       = startAt % playerNum;
    std::size_t shouldEndAt = curAt;

    while (true)
    {
        const th::PlayerAction prevAct = players[curAt]->checkLastAction();
        players[curAt]->takeAction(this->curBet);

        if (const th::chip curChipInFront = players[curAt]->checkChipInFront();
            curChipInFront > this->curBet)
        {
            th::Game::updateCurrBet(curChipInFront);
            shouldEndAt = curAt;
        }

        if (const th::PlayerAction curAct = players[curAt]->checkLastAction();
            curAct == th::PlayerAction::Fold && curAct != prevAct)
        {
            this->survivedPlayerNum--;
        }

        ++curAt;
        curAt %= playerNum;

        if (curAt == shouldEndAt)
        {
            break;
        }
    }
}

void th::Game::addToPool(const th::chip& chip)
{
    this->curPool += chip;
}

void th::Game::updateCurrBet(const th::chip& newBet)
{
    this->curBet = newBet;
}

void th::Game::showCurrPublicCards() const
{
    for (const th::PokerCard& card : this->publicCards)
    {
        std::cout << th::PokerCardUtility::toSymbol(card) << ' ';
    }

    std::cout << std::endl;
}

void th::Game::logGameStatus(const std::string& status) const
{
    std::cout << status << " starts. Now pool is " << this->curPool.val << std::endl;
}
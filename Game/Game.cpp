#include "Game.h"

#include "../Card/CardDeck.h"
#include "../Player/BasePlayer.h"

bool th::Game::initGame(const std::size_t smallBlindPos,
                        const int32_t     smallBlindChip)
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
    putSmallBlind(this->smallBlindChip, players[this->smallBlindPos]);

    const int32_t     bigBlindChip = this->smallBlindChip << 1;
    const std::size_t bigBlindPos  = (this->smallBlindPos + 1) % players.size();
    putBigBlind(bigBlindChip, players[bigBlindPos]);
}

void th::Game::dealCards(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
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
    th::Game::oneRound(this->smallBlindPos + 2, players);
}

void th::Game::flopRound(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::updateCurrBet(0);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
}

void th::Game::turnRound(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::updateCurrBet(0);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
}

void th::Game::riverRound(th::CardDeck&                                 cardDeck,
                          std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::Game::updateCurrBet(0);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
}

void th::Game::putBigBlind(const int32_t                    bigBlindChip,
                           std::shared_ptr<th::BasePlayer>& bigBlindPlayer)
{
    bigBlindPlayer->putBigBlindChip(bigBlindChip);
    th::Game::addToPull(bigBlindChip);
    th::Game::updateCurrBet(bigBlindChip);
}
void th::Game::putSmallBlind(const int32_t                    smallBlindChip,
                             std::shared_ptr<th::BasePlayer>& smallBlindPlayer)
{
    smallBlindPlayer->putSmallBlindChip(smallBlindChip);
    th::Game::addToPull(smallBlindChip);
}

void th::Game::revealOnePublicCard(th::CardDeck& cardDeck)
{
    this->publicCards.push_back(cardDeck.getCurrTopNext());
}

void th::Game::oneRound(const std::size_t                             startAt,
                        std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    const std::size_t playerNum = players.size();

    std::size_t currAt      = startAt % playerNum;
    std::size_t shouldEndAt = currAt;

    while (true)
    {
        if (players[currAt]->shouldAct() == true)
        {
            const int32_t chips = players[currAt]->takeAction(this->currBet);
            th::Game::addToPull(chips);

            if (chips > this->currBet)
            {
                th::Game::updateCurrBet(chips);
                shouldEndAt = currAt;
            }
        }
        ++currAt;
        currAt %= playerNum;

        if (currAt == shouldEndAt)
        {
            break;
        }
    }
}

void th::Game::addToPull(const int32_t chips)
{
    this->currPool += chips;
}

void th::Game::updateCurrBet(const int32_t newBet)
{
    this->currBet = newBet;
}

void th::Game::checkCurrnetPool() const
{
    std::cout << "Current pool has " << this->currPool << " chips" << std::endl;
}

void th::Game::showCurrPublicCards() const
{
    for (const th::PokerCard& card : this->publicCards)
    {
        std::cout << card.getSymbol() << ' ';
    }

    std::cout << std::endl;
}
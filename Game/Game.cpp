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
    th::Game::prepare(players);
    th::Game::dealCards(cardDeck, players);
    th::Game::preflopRound(players);
    th::Game::flopRound(cardDeck, players);
    th::Game::turnRound(cardDeck, players);
    th::Game::riverRound(cardDeck, players);
}

int32_t th::Game::getCurrPool() const
{
    return this->currPool;
}

void th::Game::prepare(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    this->survivedPlayerNum = players.size();

    players[this->smallBlindPos]->call(this->smallBlindChip);

    this->bigBlindPos = (this->smallBlindPos + 1) % this->survivedPlayerNum;

    const int32_t bigBlindChip = this->smallBlindChip << 1;
    players[this->bigBlindPos]->call(bigBlindChip);

    this->currPool += this->smallBlindChip + bigBlindChip;
    this->currCallChip = bigBlindChip;
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
    th::Game::oneRound(this->bigBlindPos + 1, players);
}

void th::Game::flopRound(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    this->currCallChip = 0;

    th::Game::revealOnePublicCard(cardDeck);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
}

void th::Game::turnRound(th::CardDeck&                                 cardDeck,
                         std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    this->currCallChip = 0;

    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
}

void th::Game::riverRound(th::CardDeck&                                 cardDeck,
                          std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    this->currCallChip = 0;

    th::Game::revealOnePublicCard(cardDeck);
    th::Game::showCurrPublicCards();
    th::Game::oneRound(this->smallBlindPos, players);
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
            const int32_t chip = players[currAt]->takeAction(this->currCallChip);
            this->currPool += chip;

            if (chip > this->currCallChip)
            {
                this->currCallChip = chip;
                shouldEndAt        = currAt;
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

void th::Game::revealOnePublicCard(th::CardDeck& cardDeck)
{
    this->publicCards.push_back(cardDeck.getCurrTopNext());
}

void th::Game::showCurrPublicCards()
{
    for (const th::PokerCard& card : this->publicCards)
    {
        std::cout << card.getSymbol() << ' ';
    }

    std::cout << std::endl;
}
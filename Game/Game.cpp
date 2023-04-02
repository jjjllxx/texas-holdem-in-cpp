#include "Game.h"

#include "../Entity/Card/CardDeck.h"
#include "../Player/BasePlayer.h"

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
    const std::size_t bigBlindPos  = (this->smallBlindPos + 1) % players.size();
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
}
void th::Game::putSmallBlind(const th::chip&                  smallBlindChip,
                             std::shared_ptr<th::BasePlayer>& smallBlindPlayer)
{
    smallBlindPlayer->putSmallBlindChip(smallBlindChip);
}

void th::Game::collectChip(std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        th::Game::addToPool(player->pushChipToPool());
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

    std::size_t currAt      = startAt % playerNum;
    std::size_t shouldEndAt = currAt;

    while (true)
    {
        if (players[currAt]->checkLastAction() != th::PlayerAction::AllIn
            || players[currAt]->checkLastAction() != th::PlayerAction::Fold)
        {
            const th::chip chipToCall = this->currBet - players[currAt]->checkChipInFront();
            const th::chip actualChip = players[currAt]->takeAction(this->currBet);

            if (actualChip > chipToCall)
            {
                th::Game::updateCurrBet(players[currAt]->checkChipInFront());
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

void th::Game::addToPool(const th::chip& chip)
{
    this->currPool += chip;
}

void th::Game::updateCurrBet(const th::chip& newBet)
{
    this->currBet = newBet;
}

void th::Game::showCurrPublicCards() const
{
    for (const th::PokerCard& card : this->publicCards)
    {
        std::cout << card.getSymbol() << ' ';
    }

    std::cout << std::endl;
}

void th::Game::logGameStatus(const std::string& status) const
{
    std::cout << status << " starts. Now pool is " << this->currPool.val << std::endl;
}
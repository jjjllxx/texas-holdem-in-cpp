#pragma once

#include "../Chip/Chip.h"

#include <memory>
#include <vector>

namespace th
{
struct CardDeck;
struct PokerCard;
class BasePlayer;

class Game
{
public:
    bool initGame(const std::size_t smallBlindPos,
                  const th::Chip&   smallBlindChip);

    void startGame(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);

private:
    std::size_t smallBlindPos;
    th::Chip    smallBlindChip;

    th::Chip currBet;
    th::Chip currPool;

    std::vector<th::PokerCard> publicCards;

    void handleBlinds(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void dealCards(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void preflopRound(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void flopRound(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void turnRound(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void riverRound(th::CardDeck&                                 cardDeck,
                    std::vector<std::shared_ptr<th::BasePlayer>>& players);

    void putBigBlind(const th::Chip&                  bigBlindChip,
                     std::shared_ptr<th::BasePlayer>& bigBlindPlayer);
    void putSmallBlind(const th::Chip&                  smallBlindChip,
                       std::shared_ptr<th::BasePlayer>& smallBlindPlayer);
    void collectChip(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void revealOnePublicCard(th::CardDeck& cardDeck);
    void oneRound(const std::size_t                             startAt,
                  std::vector<std::shared_ptr<th::BasePlayer>>& players);

    void addToPool(const th::Chip& chip);
    void updateCurrBet(const th::Chip& newBet);

    void checkCurrnetPool() const;
    void showCurrPublicCards() const;
};
} // namespace th
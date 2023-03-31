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
                  const th::chip&   smallBlindChip);

    void startGame(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);

private:
    std::size_t smallBlindPos;
    th::chip    smallBlindChip;

    th::chip currBet;
    th::chip currPool;

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

    void putBigBlind(const th::chip&                  bigBlindChip,
                     std::shared_ptr<th::BasePlayer>& bigBlindPlayer);
    void putSmallBlind(const th::chip&                  smallBlindChip,
                       std::shared_ptr<th::BasePlayer>& smallBlindPlayer);
    void collectChip(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void revealOnePublicCard(th::CardDeck& cardDeck);
    void oneRound(const std::size_t                             startAt,
                  std::vector<std::shared_ptr<th::BasePlayer>>& players);

    void addToPool(const th::chip& chip);
    void updateCurrBet(const th::chip& newBet);

    void checkCurrnetPool() const;
    void showCurrPublicCards() const;
};
} // namespace th
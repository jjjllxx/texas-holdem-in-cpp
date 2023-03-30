#pragma once

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
                  const int32_t     smallBlindChip);

    void startGame(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);

private:
    std::size_t smallBlindPos;
    int32_t     smallBlindChip;

    int32_t currBet;
    int32_t currPool;

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

    void putBigBlind(const int32_t                    bigBlindChip,
                     std::shared_ptr<th::BasePlayer>& bigBlindPlayer);
    void putSmallBlind(const int32_t                    smallBlindChip,
                       std::shared_ptr<th::BasePlayer>& smallBlindPlayer);
    void revealOnePublicCard(th::CardDeck& cardDeck);
    void oneRound(const std::size_t                             startAt,
                  std::vector<std::shared_ptr<th::BasePlayer>>& players);

    void addToPull(const int32_t chips);
    void updateCurrBet(const int32_t newBet);

    void checkCurrnetPool() const;
    void showCurrPublicCards() const;
};
} // namespace th
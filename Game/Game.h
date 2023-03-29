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

    int32_t getCurrPool() const;

private:
    std::size_t bigBlindPos;
    std::size_t smallBlindPos;

    int32_t currPool;
    int32_t smallBlindChip;
    int32_t currCallChip;

    int32_t survivedPlayerNum;

    std::vector<th::PokerCard> publicCards;

    void prepare(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void dealCards(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void preflopRound(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void flopRound(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void turnRound(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void riverRound(th::CardDeck&                                 cardDeck,
                    std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void oneRound(const std::size_t                             startAt,
                  std::vector<std::shared_ptr<th::BasePlayer>>& players);

    void revealOnePublicCard(th::CardDeck& cardDeck);
    void showCurrPublicCards();
};
} // namespace th

#pragma once

#include "Entity/Chip/Chip.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace th
{
struct CardDeck;
struct PokerCard;
class BasePlayer;

class Game
{
public:
    bool initGame(const std::size_t playersCnt,
                  const std::size_t smallBlindPos,
                  const th::chip&   smallBlindChip);
    void startGame(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);

private:
    th::chip    curPool;
    th::chip    smallBlindChip;
    std::size_t smallBlindPos;
    std::size_t allInPlayersCnt;
    std::size_t unfoldPlayersCnt;

    std::vector<th::PokerCard> communityCards;

    void handleBlinds(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void dealCards(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void oneRound(const std::size_t                             cardNumToReveal,
                  const std::string&                            roundName,
                  th::CardDeck&                                 cardDeck,
                  std::vector<std::shared_ptr<th::BasePlayer>>& players);

    void logGameStatus(const std::string& status) const;
    void revealPublicCards(const std::size_t cardNumToReveal,
                           th::CardDeck&     cardDeck);
    void showCurrPublicCards() const;
    void playersTakeAction(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void collectChips(std::vector<std::shared_ptr<th::BasePlayer>>& players);
};
} // namespace th
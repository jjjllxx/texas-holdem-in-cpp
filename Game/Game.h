#pragma once

#include <memory>
#include <vector>

namespace th
{
struct CardDeck;
class BasePlayer;

class Game
{
public:
    Game();
    ~Game() = default;

    bool initGame(const std::size_t smallBlindPos,
                  const int32_t     smallBlindChip);

    void startGame(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);

    int32_t getCurrPool() const;

private:
    int32_t currPool;

    std::size_t bigBlindPos;
    std::size_t smallBlindPos;
    int32_t     smallBlindChip;

    void dealCards(th::CardDeck&                                 cardDeck,
                   std::vector<std::shared_ptr<th::BasePlayer>>& players);
};
} // namespace th

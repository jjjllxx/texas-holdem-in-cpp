#pragma once

#include <memory>
#include <vector>

namespace th
{
class BasePlayer;

class Game
{
public:
    Game();
    ~Game() = default;

    bool initGame(const std::size_t smallBlindPos,
                  const int32_t     smallBlindChip);
    void startGame(std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void endGame(std::vector<std::shared_ptr<th::BasePlayer>>& players);

    int32_t getCurrPool() const;

private:
    int32_t currPool;

    std::size_t smallBlindPos;
    int32_t     smallBlindChip;
};
} // namespace th

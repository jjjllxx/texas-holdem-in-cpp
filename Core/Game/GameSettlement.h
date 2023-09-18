#pragma once

#include <memory>
#include <vector>

namespace th
{
struct chip;
struct PokerCard;
class BasePlayer;

struct PlayerWithHand
{
    std::shared_ptr<th::BasePlayer> player;
    std::vector<th::PokerCard>      hand;
};

namespace GameSettlement
{
    std::vector<std::shared_ptr<th::BasePlayer>> decideWinners(const std::vector<th::PokerCard>&                   communityCards,
                                                               const std::vector<std::shared_ptr<th::BasePlayer>>& players);
    std::vector<std::shared_ptr<th::BasePlayer>> extractSurvivors(const std::vector<std::shared_ptr<th::BasePlayer>>& players);
    std::vector<th::PlayerWithHand>              calcHighestHand(const std::vector<th::PokerCard>&                   communityCards,
                                                                 const std::vector<std::shared_ptr<th::BasePlayer>>& survivors);

    void        sortByHand(std::vector<th::PlayerWithHand>& survivorsWithCards);
    void        logRank(const std::size_t                      winnersCnt,
                        const std::vector<th::PlayerWithHand>& sortedSurvivors);
    std::size_t countWinners(const std::vector<th::PlayerWithHand>& sortedSurvivors);

    std::vector<th::PokerCard> combineCards(const std::vector<th::PokerCard>& holeCards,
                                            const std::vector<th::PokerCard>& communityCards);

} // namespace GameSettlement
} // namespace th
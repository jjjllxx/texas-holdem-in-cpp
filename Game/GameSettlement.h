#pragma once

#include <cstddef>
#include <iterator>
#include <vector>

namespace th
{
struct chip;
struct PokerCard;
class BasePlayer;

struct PlayerWithCards
{
    std::shared_ptr<th::BasePlayer> player;
    std::vector<th::PokerCard>      cards;
};

namespace GameSettlement
{
    std::vector<std::shared_ptr<th::BasePlayer>> decideWinners(const std::vector<th::PokerCard>&                   publicCards,
                                                               const std::vector<std::shared_ptr<th::BasePlayer>>& players);
    std::vector<std::shared_ptr<th::BasePlayer>> extractSurvivors(const std::vector<std::shared_ptr<th::BasePlayer>>& players);
    std::vector<th::PlayerWithCards>             calcHighestCardCombo(const std::vector<th::PokerCard>&                   publicCards,
                                                                      const std::vector<std::shared_ptr<th::BasePlayer>>& survivors);

    void        sortByCardCombo(std::vector<th::PlayerWithCards>& survivorsWithCards);
    void        logRank(const std::size_t                       winnerCnt,
                        const std::vector<th::PlayerWithCards>& sortedSurvivors);
    std::size_t countWinners(const std::vector<th::PlayerWithCards>& sortedSurvivors);

    std::vector<th::PokerCard> combineCards(const std::vector<th::PokerCard>& handCards,
                                            const std::vector<th::PokerCard>& publicCards);

} // namespace GameSettlement
} // namespace th
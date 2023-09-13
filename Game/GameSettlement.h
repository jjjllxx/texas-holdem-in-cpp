#pragma once

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
    std::shared_ptr<th::BasePlayer>              decideWinner(const std::vector<th::PokerCard>&                   publicCards,
                                                              const std::vector<std::shared_ptr<th::BasePlayer>>& players);
    std::vector<std::shared_ptr<th::BasePlayer>> extractSurvivors(const std::vector<std::shared_ptr<th::BasePlayer>>& players);
    std::vector<th::PlayerWithCards>             calcHighestCardCombo(const std::vector<th::PokerCard>&                   publicCards,
                                                                      const std::vector<std::shared_ptr<th::BasePlayer>>& survivors);

    void sortByCardCombo(std::vector<th::PlayerWithCards>& cardCombos);
    void logRank(const std::vector<th::PlayerWithCards>& cardCombos);

    std::vector<th::PokerCard> combineCards(const std::vector<th::PokerCard>& handCards,
                                            const std::vector<th::PokerCard>& publicCards);

} // namespace GameSettlement
} // namespace th
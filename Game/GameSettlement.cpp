#include "GameSettlement.h"

#include "Algorithms/PokerHand/HandComparison.h"
#include "Algorithms/PokerHand/HandSelection.h"
#include "Entity/Card/PokerCard.h"
#include "Player/BasePlayer.h"

#include <algorithm>
#include <iostream>

std::vector<std::shared_ptr<th::BasePlayer>> th::GameSettlement::decideWinners(const std::vector<th::PokerCard>&                   communityCards,
                                                                               const std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    const std::vector<std::shared_ptr<th::BasePlayer>> survivors = th::GameSettlement::extractSurvivors(players);

    std::vector<th::PlayerWithHand> survivorsWithHand = th::GameSettlement::calcHighestHand(communityCards, survivors);
    th::GameSettlement::sortByHand(survivorsWithHand);

    const std::size_t winnersCnt = th::GameSettlement::countWinners(survivorsWithHand);
    th::GameSettlement::logRank(winnersCnt, survivorsWithHand);
    std::vector<std::shared_ptr<th::BasePlayer>> winners;

    for (std::size_t i = 0; i < winnersCnt; ++i)
    {
        winners.push_back(survivorsWithHand[i].player);
    }

    return winners;
}

std::vector<std::shared_ptr<th::BasePlayer>> th::GameSettlement::extractSurvivors(const std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    std::vector<std::shared_ptr<th::BasePlayer>> survivors;

    for (const auto& player : players)
    {
        if (player->checkLastAction() != th::PlayerAction::Fold)
        {
            survivors.push_back(player);
        }
    }

    return survivors;
}

std::vector<th::PlayerWithHand> th::GameSettlement::calcHighestHand(const std::vector<th::PokerCard>&                   communityCards,
                                                                    const std::vector<std::shared_ptr<th::BasePlayer>>& survivors)
{
    std::vector<th::PlayerWithHand> playersWithCards;
    playersWithCards.reserve(survivors.size());
    for (const std::shared_ptr<th::BasePlayer>& survivor : survivors)
    {
        th::PlayerWithHand pwc;
        pwc.player = survivor;
        pwc.hand   = th::HandSelection::selectHighestHand(
            th::GameSettlement::combineCards(survivor->checkHandCards(),
                                             communityCards));
        playersWithCards.push_back(pwc);
    }

    return playersWithCards;
}

void th::GameSettlement::sortByHand(std::vector<th::PlayerWithHand>& survivorsWithCards)
{
    std::sort(survivorsWithCards.begin(),
              survivorsWithCards.end(),
              [](const th::PlayerWithHand& a, const th::PlayerWithHand& b)
              {
                  return th::HandComparison::compareHand(a.hand,
                                                         b.hand)
                         == th::HandCmpResult::Win;
              });
}

void th::GameSettlement::logRank(const std::size_t                      winnersCnt,
                                 const std::vector<th::PlayerWithHand>& sortedSurvivors)
{
    std::cout << "\nThe rank of this game: " << std::endl;
    std::size_t rank = 1;

    for (const th::PlayerWithHand& player : sortedSurvivors)
    {
        const std::string winnerMarker = rank <= winnersCnt ? "(winner)" : "";
        std::cout << rank << ". " << player.player->getName() << " with hole cards "
                  << th::PokerCardUtility::toSymbol(player.player->checkHandCards())
                  << "can generate highest combination: "
                  << th::PokerCardUtility::toSymbol(th::HandComparison::deduceHandCmpOrder(player.hand))
                  << winnerMarker << std::endl;
        ++rank;
    }
}

std::size_t th::GameSettlement::countWinners(const std::vector<th::PlayerWithHand>& sortedSurvivors)
{
    std::size_t winnersCnt = 1;

    for (std::size_t i = 1; i < sortedSurvivors.size(); ++i)
    {
        if (th::HandComparison::compareHand(sortedSurvivors[i - 1].hand,
                                            sortedSurvivors[i].hand)
            != th::HandCmpResult::Draw)
        {
            break;
        }

        ++winnersCnt;
    }

    return winnersCnt;
}

std::vector<th::PokerCard> th::GameSettlement::combineCards(const std::vector<th::PokerCard>& holeCards,
                                                            const std::vector<th::PokerCard>& communityCards)
{
    std::vector<th::PokerCard> allCards(communityCards);
    allCards.reserve(holeCards.size() + communityCards.size());
    allCards.insert(allCards.end(), holeCards.begin(), holeCards.end());

    return allCards;
}
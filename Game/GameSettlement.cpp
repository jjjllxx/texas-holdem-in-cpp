#include "GameSettlement.h"

#include "Algorithms/PokerHand/HandComparison.h"
#include "Algorithms/PokerHand/HandSelection.h"
#include "Entity/Card/PokerCard.h"
#include "Player/BasePlayer.h"

#include <algorithm>
#include <iostream>

std::vector<std::shared_ptr<th::BasePlayer>> th::GameSettlement::decideWinners(const std::vector<th::PokerCard>&                   publicCards,
                                                                               const std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    const std::vector<std::shared_ptr<th::BasePlayer>> survivors = th::GameSettlement::extractSurvivors(players);

    std::vector<th::PlayerWithCards> survivorsWithCards = th::GameSettlement::calcHighestHand(publicCards, survivors);
    th::GameSettlement::sortByHand(survivorsWithCards);

    const std::size_t winnersCnt = th::GameSettlement::countWinners(survivorsWithCards);
    th::GameSettlement::logRank(winnersCnt, survivorsWithCards);
    std::vector<std::shared_ptr<th::BasePlayer>> winners;

    for (std::size_t i = 0; i < winnersCnt; ++i)
    {
        winners.push_back(survivorsWithCards[i].player);
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

std::vector<th::PlayerWithCards> th::GameSettlement::calcHighestHand(const std::vector<th::PokerCard>&                   publicCards,
                                                                     const std::vector<std::shared_ptr<th::BasePlayer>>& survivors)
{
    std::vector<th::PlayerWithCards> playersWithCards;
    playersWithCards.reserve(survivors.size());
    for (const std::shared_ptr<th::BasePlayer>& survivor : survivors)
    {
        th::PlayerWithCards pwc;
        pwc.player = survivor;
        pwc.cards  = th::HandSelection::selectHighestHand(
            th::GameSettlement::combineCards(survivor->checkHandCards(),
                                             publicCards));
        playersWithCards.push_back(pwc);
    }

    return playersWithCards;
}

void th::GameSettlement::sortByHand(std::vector<th::PlayerWithCards>& survivorsWithCards)
{
    std::sort(survivorsWithCards.begin(),
              survivorsWithCards.end(),
              [](const th::PlayerWithCards& a, const th::PlayerWithCards& b)
              {
                  return th::HandComparison::compareHand(a.cards,
                                                         b.cards)
                         == th::HandCmpResult::Win;
              });
}

void th::GameSettlement::logRank(const std::size_t                       winnersCnt,
                                 const std::vector<th::PlayerWithCards>& sortedSurvivors)
{
    std::cout << "\nThe rank of this game: " << std::endl;
    std::size_t rank = 1;

    for (const th::PlayerWithCards& player : sortedSurvivors)
    {
        const std::string winnerMarker = rank <= winnersCnt ? "(winner)" : "";
        std::cout << rank << ". " << player.player->getName() << " with hand cards "
                  << th::PokerCardUtility::toSymbol(player.player->checkHandCards())
                  << "can generate highest combination: "
                  << th::PokerCardUtility::toSymbol(th::HandComparison::deduceCardCmpOrder(player.cards))
                  << winnerMarker << std::endl;
        ++rank;
    }
}

std::size_t th::GameSettlement::countWinners(const std::vector<th::PlayerWithCards>& sortedSurvivors)
{
    std::size_t winnersCnt = 1;

    for (std::size_t i = 1; i < sortedSurvivors.size(); ++i)
    {
        if (th::HandComparison::compareHand(sortedSurvivors[i - 1].cards,
                                            sortedSurvivors[i].cards)
            != th::HandCmpResult::Draw)
        {
            break;
        }

        ++winnersCnt;
    }

    return winnersCnt;
}

std::vector<th::PokerCard> th::GameSettlement::combineCards(const std::vector<th::PokerCard>& handCards,
                                                            const std::vector<th::PokerCard>& publicCards)
{
    std::vector<th::PokerCard> allCards(publicCards);
    allCards.reserve(handCards.size() + publicCards.size());
    allCards.insert(allCards.end(), handCards.begin(), handCards.end());

    return allCards;
}
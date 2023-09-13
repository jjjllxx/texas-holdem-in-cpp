#include "GameSettlement.h"

#include "Algorithms/Card/CardComparison.h"
#include "Algorithms/Card/CardSelector.h"
#include "Entity/Card/PokerCard.h"
#include "Player/BasePlayer.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>

std::shared_ptr<th::BasePlayer> th::GameSettlement::decideWinner(const std::vector<th::PokerCard>&                   publicCards,
                                                                 const std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    const std::vector<std::shared_ptr<th::BasePlayer>> survivors = th::GameSettlement::extractSurvivors(players);

    auto cardCombos = th::GameSettlement::calcHighestCardCombo(publicCards, survivors);
    th::GameSettlement::sortByCardCombo(cardCombos);
    th::GameSettlement::logRank(cardCombos);

    return cardCombos.front().player;
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

std::vector<th::PlayerWithCards> th::GameSettlement::calcHighestCardCombo(const std::vector<th::PokerCard>&                   publicCards,
                                                                          const std::vector<std::shared_ptr<th::BasePlayer>>& survivors)
{
    std::vector<th::PlayerWithCards> playersWithCards;
    playersWithCards.reserve(survivors.size());
    for (const std::shared_ptr<th::BasePlayer>& survivor : survivors)
    {
        th::PlayerWithCards pwc;
        pwc.player = survivor;
        pwc.cards  = th::CardSelector::selectHighestCardCombo(
            th::GameSettlement::combineCards(survivor->checkHandCards(),
                                             publicCards));
        playersWithCards.push_back(pwc);
    }

    return playersWithCards;
}

void th::GameSettlement::sortByCardCombo(std::vector<th::PlayerWithCards>& cardCombos)
{
    std::sort(cardCombos.begin(),
              cardCombos.end(),
              [](const th::PlayerWithCards& a, const th::PlayerWithCards& b)
              {
                  return th::CardComparison::compareCardCombo(a.cards,
                                                              b.cards)
                         == th::CardComboCmpResult::Win;
              });
}

void th::GameSettlement::logRank(const std::vector<th::PlayerWithCards>& cardCombos)
{
    std::cout << "The rank of this game: " << std::endl;

    std::size_t rank = 1;
    for (const th::PlayerWithCards& pwc : cardCombos)
    {
        std::cout << rank << ". Player " << pwc.player->getId() << " with hand cards "
                  << th::PokerCardUtility::toSymbol(pwc.player->checkHandCards())
                  << "can generate highest combination: "
                  << th::PokerCardUtility::toSymbol(th::CardComparison::deduceCardCmpOrder(pwc.cards)) << std::endl;
        ++rank;
    }
}

std::vector<th::PokerCard> th::GameSettlement::combineCards(const std::vector<th::PokerCard>& handCards,
                                                            const std::vector<th::PokerCard>& publicCards)
{
    std::vector<th::PokerCard> allCards(publicCards);
    allCards.reserve(handCards.size() + publicCards.size());
    allCards.insert(allCards.end(), handCards.begin(), handCards.end());

    return allCards;
}
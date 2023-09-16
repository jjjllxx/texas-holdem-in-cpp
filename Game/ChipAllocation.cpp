#include "ChipAllocation.h"

#include "Entity/Chip/Chip.h"
#include "Player/BasePlayer.h"

#include <algorithm>
#include <iostream>
#include <memory>

void th::ChipAllocation::allocateChip(std::vector<std::shared_ptr<th::BasePlayer>>& winners,
                                      std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    th::ChipAllocation::sortWinnersByChipForCurGame(winners);
    const std::vector<th::chip> pools = th::ChipAllocation::dividePools(players, winners);
    th::ChipAllocation::logPools(pools);
    th::ChipAllocation::allocateChipToWinners(pools, winners);
    th::ChipAllocation::takeBackExtraChip(winners.back()->checkChipForCurGame(), players);
    th::ChipAllocation::logChipInfo(players);
}

void th::ChipAllocation::sortWinnersByChipForCurGame(std::vector<std::shared_ptr<th::BasePlayer>>& winners)
{
    std::sort(winners.begin(),
              winners.end(),
              [](const std::shared_ptr<th::BasePlayer>& a,
                 const std::shared_ptr<th::BasePlayer>& b)
              {
                  return a->checkChipForCurGame() < b->checkChipForCurGame();
              });
}

std::vector<th::chip> th::ChipAllocation::dividePools(const std::vector<std::shared_ptr<th::BasePlayer>>& players,
                                                      const std::vector<std::shared_ptr<th::BasePlayer>>& sortedWinners)
{
    std::vector<th::chip> pools;
    pools.reserve(sortedWinners.size());

    th::chip prevLevel = 0;

    for (const std::shared_ptr<th::BasePlayer>& winner : sortedWinners)
    {
        th::chip       curPool = 0;
        const th::chip level   = winner->checkChipForCurGame();

        for (const std::shared_ptr<th::BasePlayer>& player : players)
        {
            curPool += std::max(std::min(player->checkChipForCurGame(), level) - prevLevel, th::chip { 0 });
        }

        prevLevel = level;
        pools.push_back(curPool);
    }

    return pools;
}

void th::ChipAllocation::allocateChipToWinners(const std::vector<th::chip>&                  pools,
                                               std::vector<std::shared_ptr<th::BasePlayer>>& sortedWinners)
{
    const std::size_t winnersCnt = sortedWinners.size();

    for (std::size_t i = 0; i < winnersCnt; ++i)
    {
        for (std::size_t j = i; j < winnersCnt; ++j)
        {
            const th::chip chipToReceive { static_cast<int32_t>(pools[i].val / winnersCnt - i) };
            sortedWinners[j]->receiveChip(chipToReceive);
            std::cout << sortedWinners[j]->getName() << " has received " << chipToReceive.val << " chips" << std::endl;
        }
    }
}

void th::ChipAllocation::takeBackExtraChip(const th::chip&                               highestLevel,
                                           std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    std::cout << "\nHighest bet is " << highestLevel.val << std::endl;

    for (std::shared_ptr<th::BasePlayer>& player : players)
    {
        const th::chip chipToTakeBack { std::max(player->checkChipForCurGame() - highestLevel, th::chip { 0 }) };
        player->receiveChip(chipToTakeBack);
        std::cout << player->getName() << " has put "
                  << player->checkChipForCurGame().val << " for this game,"
                  << " so take back " << chipToTakeBack.val << " chips" << std::endl;
    }
}

void th::ChipAllocation::logPools(const std::vector<th::chip>& pools)
{
    std::size_t poolRank = 1;
    for (const th::chip& pool : pools)
    {
        std::cout << "\nPool " << poolRank << " has " << pool.val << " chip." << std::endl;
        poolRank++;
    }
}

void th::ChipAllocation::logChipInfo(const std::vector<std::shared_ptr<th::BasePlayer>>& players)
{
    std::cout << "\nPlayer Chip Situation: " << std::endl;

    for (const std::shared_ptr<th::BasePlayer>& player : players)
    {
        std::cout << player->getName() << " now has "
                  << player->checkChip().val << " chip." << std::endl;
    }
}
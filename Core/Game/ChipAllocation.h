#pragma once

#include <memory>
#include <utility>
#include <vector>

namespace th
{
struct chip;
class BasePlayer;

namespace ChipAllocation
{
    void allocateChip(std::vector<std::shared_ptr<th::BasePlayer>>& winners,
                      std::vector<std::shared_ptr<th::BasePlayer>>& players);

    void                  sortWinnersByChipForCurGame(std::vector<std::shared_ptr<th::BasePlayer>>& winners);
    std::vector<th::chip> dividePools(const std::vector<std::shared_ptr<th::BasePlayer>>& players,
                                      const std::vector<std::shared_ptr<th::BasePlayer>>& sortedWinners);

    void allocateChipToWinners(const std::vector<th::chip>&                  pools,
                               std::vector<std::shared_ptr<th::BasePlayer>>& sortedWinners);
    void takeBackExtraChip(const th::chip&                               highestLevel,
                           std::vector<std::shared_ptr<th::BasePlayer>>& players);
    void logPools(const std::vector<th::chip>& pools);
    void logChipInfo(const std::vector<std::shared_ptr<th::BasePlayer>>& players);
} // namespace ChipAllocation
} // namespace th
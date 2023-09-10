#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace th
{
inline constexpr std::size_t MINIMUM_PLAYER_NUM = 2;
inline constexpr std::size_t MAXIMUM_PLAYER_NUM = 12;

inline constexpr std::size_t STANDARD_HAND_CARD_SIZE  = 2;
inline constexpr std::size_t STANDARD_CARD_COMBO_SIZE = 5;
inline constexpr std::size_t STANDARD_CARD_DECK_SIZE  = 52;

inline const std::string PREFLOP_ROUND = "Preflop Round";
inline const std::string FLOP_ROUND    = "Flop Round";
inline const std::string TURN_ROUND    = "Turn Round";
inline const std::string RIVER_ROUND   = "River Round";
} // namespace th
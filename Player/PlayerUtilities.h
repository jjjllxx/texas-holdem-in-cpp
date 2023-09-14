#pragma once

#include <string>

namespace th
{
struct chip;
enum class PlayerAction;

namespace PlayerUtilities
{
    void logPlayerStatus(const th::PlayerAction lastAction,
                         const th::chip&        chipInFront,
                         const std::string&     name);

    bool needToAct(const std::string&     name,
                   const th::PlayerAction lastAction);
} // namespace PlayerUtilities
} // namespace th
#pragma once

namespace th
{
namespace LoggerInitialiser
{
    enum class Mode
    {
        Debug,
        Release
    };

    void init(const Mode mode);
} // namespace LoggerInitialiser
} // namespace th
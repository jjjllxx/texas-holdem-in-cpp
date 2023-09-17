#pragma once

#include <cstdint>

namespace th
{
struct score // NOLINT
{
    score();
    score(const int32_t val);

    int32_t val;

    th::score operator-(const th::score& score) const;
    th::score operator+(const th::score& score) const;
    th::score operator*(const int32_t val) const;

    th::score& operator+=(const th::score& score);
    th::score& operator-=(const th::score& score);

    bool operator==(const th::score& score) const;
    bool operator<(const th::score& score) const;
    bool operator>(const th::score& score) const;
    bool operator<=(const th::score& score) const;
    bool operator>=(const th::score& score) const;
};
} // namespace th
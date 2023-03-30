#pragma once

#include <cstdint>

namespace th
{
struct Chip
{
    Chip();
    Chip(const int32_t val);

    int32_t val;

    th::Chip operator-(const th::Chip& chip) const;
    th::Chip operator-(const int32_t val) const;
    th::Chip operator+(const th::Chip& chip) const;
    th::Chip operator*(const int32_t val) const;
    th::Chip operator*(const double val) const;

    th::Chip& operator+=(const th::Chip& chip);
    th::Chip& operator-=(const th::Chip& chip);

    bool operator==(const th::Chip& chip) const;
    bool operator<(const th::Chip& chip) const;
    bool operator>(const th::Chip& chip) const;
    bool operator<=(const th::Chip& chip) const;
    bool operator>=(const th::Chip& chip) const;
};

} // namespace th
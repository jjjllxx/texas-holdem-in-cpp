#pragma once

#include <cstdint>

namespace th
{
struct chip // NOLINT
{
    chip();
    chip(const int32_t val);

    int32_t val;

    th::chip operator-(const th::chip& chip) const;
    th::chip operator+(const th::chip& chip) const;
    th::chip operator*(const int32_t val) const;
    th::chip operator*(const double val) const;

    th::chip& operator+=(const th::chip& chip);
    th::chip& operator-=(const th::chip& chip);

    bool operator==(const th::chip& chip) const;
    bool operator<(const th::chip& chip) const;
    bool operator>(const th::chip& chip) const;
    bool operator<=(const th::chip& chip) const;
    bool operator>=(const th::chip& chip) const;
};

} // namespace th
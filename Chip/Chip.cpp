#include "Chip.h"

th::Chip::Chip() :
    val(0)
{
}

th::Chip::Chip(const int32_t val) :
    val(val)
{
}

th::Chip th::Chip::operator+(const th::Chip& chip) const
{
    return this->val + chip.val;
}

th::Chip th::Chip::operator-(const th::Chip& chip) const
{
    return this->val + chip.val;
}

th::Chip th::Chip::operator*(const int32_t val) const
{
    return this->val * val;
}

th::Chip th::Chip::operator*(const double val) const
{
    return this->val * val;
}

th::Chip& th::Chip::operator+=(const th::Chip& chip)
{
    this->val += chip.val;
    return *this;
}

th::Chip& th::Chip::operator-=(const th::Chip& chip)
{
    this->val -= chip.val;
    return *this;
}

bool th::Chip::operator==(const th::Chip& chip) const
{
    return this->val == chip.val;
}

bool th::Chip::operator<(const th::Chip& chip) const
{
    return this->val < chip.val;
}

bool th::Chip::operator>(const th::Chip& chip) const
{
    return this->val > chip.val;
}

bool th::Chip::operator<=(const th::Chip& chip) const
{
    return this->val <= chip.val;
}

bool th::Chip::operator>=(const th::Chip& chip) const
{
    return this->val >= chip.val;
}
#include "Chip.h"

th::chip::chip() :
    val(0)
{
}

th::chip::chip(const int32_t val) :
    val(val)
{
}

th::chip th::chip::operator+(const th::chip& chip) const
{
    return this->val + chip.val;
}

th::chip th::chip::operator-(const th::chip& chip) const
{
    return this->val - chip.val;
}

th::chip th::chip::operator*(const int32_t val) const
{
    return this->val * val;
}

th::chip th::chip::operator*(const double val) const
{
    return this->val * val;
}

th::chip& th::chip::operator+=(const th::chip& chip)
{
    this->val += chip.val;
    return *this;
}

th::chip& th::chip::operator-=(const th::chip& chip)
{
    this->val -= chip.val;
    return *this;
}

bool th::chip::operator==(const th::chip& chip) const
{
    return this->val == chip.val;
}

bool th::chip::operator<(const th::chip& chip) const
{
    return this->val < chip.val;
}

bool th::chip::operator>(const th::chip& chip) const
{
    return this->val > chip.val;
}

bool th::chip::operator<=(const th::chip& chip) const
{
    return this->val <= chip.val;
}

bool th::chip::operator>=(const th::chip& chip) const
{
    return this->val >= chip.val;
}
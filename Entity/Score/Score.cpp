#include "Score.h"

th::score::score() :
    val(0)
{
}

th::score::score(const int32_t val) :
    val(val)
{
}

th::score th::score::operator+(const th::score& score) const
{
    return this->val + score.val;
}

th::score th::score::operator-(const th::score& score) const
{
    return this->val - score.val;
}

th::score th::score::operator*(const int32_t val) const
{
    return this->val * val;
}

th::score& th::score::operator+=(const th::score& score)
{
    this->val += score.val;
    return *this;
}

th::score& th::score::operator-=(const th::score& score)
{
    this->val -= score.val;
    return *this;
}

bool th::score::operator==(const th::score& score) const
{
    return this->val == score.val;
}

bool th::score::operator<(const th::score& score) const
{
    return this->val < score.val;
}

bool th::score::operator>(const th::score& score) const
{
    return this->val > score.val;
}

bool th::score::operator<=(const th::score& score) const
{
    return this->val <= score.val;
}

bool th::score::operator>=(const th::score& score) const
{
    return this->val >= score.val;
}
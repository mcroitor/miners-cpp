#include "base.hpp"

Base::Base(const Point &p) : position(p) {}

Point Base::GetPosition() const
{
    return position;
}
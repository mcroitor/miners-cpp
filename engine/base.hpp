#ifndef _BASE_HPP_
#define _BASE_HPP_

#include "point.hpp"

class Base {
    Point position;
public:
    Base(const Point& p);
    Point GetPosition() const;
};

#endif
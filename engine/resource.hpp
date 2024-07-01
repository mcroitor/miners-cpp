#ifndef _RESOURCE_HPP_
#define _RESOURCE_HPP_

#include "point.hpp"

class Resource {
    Point position;
    int amount;

public:
    Resource(const Point&, int);
    Point GetPosition() const;
    int GetAmount() const;
    void Mine();
};

#endif

#include "resource.hpp"

Resource::Resource(const Point& p, int a) : position(p), amount(a) {}

Point Resource::GetPosition() const {
    return position;
}

int Resource::GetAmount() const {
    return amount;
}

void Resource::Mine() {
    if(amount > 0) {
        --amount;
    }
}
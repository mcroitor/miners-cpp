#include "point.hpp"

int Abs(int p) {
    return (p < 0) ? -p : p;
}

Point::Point(int _x, int _y)
: x(_x), y(_y)
{}

Point::Point(const Point &pt)
    : x(pt.GetX()), y(pt.GetY())
{}

void Point::operator=(const Point &pt) {
    x = pt.GetX();
    y = pt.GetY();
}

int Point::GetX() const { return x; }

int Point::GetY() const { return y; }

bool operator == (const Point& pt1, const Point& pt2)
{
    return Distance(pt1, pt2) < 0.01;
}
int Distance (const Point& pt1, const Point& pt2){
    return Abs(pt1.GetX() - pt2.GetX()) + 
        Abs(pt1.GetY() - pt2.GetY());
}

#ifndef _POINT_HPP_
#define _POINT_HPP_

constexpr int MAX_SIZE = 100.0f;

class Point {
    int x;
    int y;

public:
    Point() = default;
    Point(int, int);
    Point(const Point&);
    void operator = (const Point&);
    
    int GetX() const;
    int GetY() const;
};

bool operator == (const Point&, const Point&);
int Distance (const Point&, const Point&);

#endif
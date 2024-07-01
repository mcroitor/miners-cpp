#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "definitions.hpp"
#include "robot_config.hpp"
#include "point.hpp"

#include <string>

class AsteroidMap;
class Robot;

typedef ACTION (*GetActionFunction)(const Robot&, const AsteroidMap &);

class Robot {
    RobotConfig config;
    float deltaX = 0.;
    float deltaY = 0.;
    Point position;
    size_t amount;
    GetActionFunction getActionFunction;
public:
    Robot(const RobotConfig& rc, const Point& p, GetActionFunction f);
    Robot(const Robot&);
    virtual ~Robot() = default;
    void operator = (const Robot&);

    Point GetPosition() const;
    size_t GetCapacity() const;
    size_t GetAmount() const;
    float GetSpeed() const;
    std::string GetName() const;
    
    bool IsFull() const;
    bool IsEmpty() const;
    void Move(ACTION a);
    void Mine();
    void Unload();

    ACTION GetAction(const AsteroidMap &) const;
};

#endif

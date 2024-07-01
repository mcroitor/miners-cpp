#include "robot.hpp"

Robot::Robot(const RobotConfig &rc, const Point &p, GetActionFunction f)
    : config(rc), position(p), amount(0), getActionFunction(f) {}

Robot::Robot(const Robot &r)
    : config(r.config),
      position(r.position),
      amount(r.amount),
      getActionFunction(r.getActionFunction) {}

void Robot::operator=(const Robot &r)
{
    if (this != &r)
    {
        config = r.config;
        position = r.position;
        amount = r.amount;
        getActionFunction = r.getActionFunction;
    }
}

Point Robot::GetPosition() const
{
    return position;
}

size_t Robot::GetCapacity() const
{
    return config.capacity;
}

size_t Robot::GetAmount() const
{
    return amount;
}

float Robot::GetSpeed() const
{
    return config.speed;
}

std::string Robot::GetName() const
{
    return config.name;
}

bool Robot::IsFull() const
{
    return amount == config.capacity;
}

bool Robot::IsEmpty() const
{
    return amount == 0;
}

void Robot::Move(ACTION a)
{
    switch (a)
    {
    case ACTION::UP:
        deltaY += GetSpeed();
        if(deltaY >= 1.0)
        {
            position = Point(position.GetX(), (position.GetY() + 1) % MAX_SIZE);
            deltaY = 0.0;
        }
        break;
    case ACTION::DOWN:
        deltaY += GetSpeed();
        if(deltaY >= 1.0)
        {
            position = Point(position.GetX(), position.GetY() - 1);
            deltaY = 0.0;
        }
        break;
    case ACTION::LEFT:
        deltaX += GetSpeed();
        if(deltaX >= 1.0)
        {
            position = Point(position.GetX() - 1, position.GetY());
            deltaX = 0.0;
        }
        break;
    case ACTION::RIGHT:
        deltaX += GetSpeed();
        if(deltaX >= 1.0)
        {
            position = Point((position.GetX() + 1) % MAX_SIZE, position.GetY());
            deltaX = 0.0;
        }
        break;
    }
}

void Robot::Mine()
{
    if (amount < config.capacity)
    {
        amount++;
    }
}

void Robot::Unload()
{
    amount = 0;
}

ACTION Robot::GetAction(const AsteroidMap &a) const
{
    return getActionFunction(*this, a);
}

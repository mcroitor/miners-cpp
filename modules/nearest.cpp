#include "nearest.hpp"

ACTION NearestGetAction(const Robot& robot, const AsteroidMap &a)
{
    // if the robot is full and at the base, do unload
    if(robot.IsFull() && a.IsOnBase(robot))
    {
        return ACTION::UNLOAD;
    }
    // if the robot is full and not at the base, return to the nearest base
    if(robot.IsFull() && !a.IsOnBase(robot))
    {
        Base nearestBase = a.GetNearestBase(robot);
        // horizontal movement
        if(nearestBase.GetPosition().GetX() > robot.GetPosition().GetX())
        {
            return ACTION::RIGHT;
        }
        if(nearestBase.GetPosition().GetX() < robot.GetPosition().GetX())
        {
            return ACTION::LEFT;
        }
        // vertical movement
        if(nearestBase.GetPosition().GetY() > robot.GetPosition().GetY())
        {
            return ACTION::UP;
        }
        if(nearestBase.GetPosition().GetY() < robot.GetPosition().GetY())
        {
            return ACTION::DOWN;
        }
    }
    // if the robot is not full and at the resource, do mine
    if(a.IsOnResource(robot))
    {
        return ACTION::MINE;
    }
    // if the robot is not full, move to the nearest resource
    Resource nearest = a.GetResources().front();
    float distance = Distance(nearest.GetPosition(), robot.GetPosition());
    for(const Resource &r : a.GetResources())
    {
        if(distance > Distance(r.GetPosition(), robot.GetPosition()) && r.GetAmount() > 0)
        {
            nearest = r;
            distance = Distance(r.GetPosition(), robot.GetPosition());
        }
    }
    // horizontal movement
    if(nearest.GetPosition().GetX() > robot.GetPosition().GetX())
    {
        return ACTION::RIGHT;
    }
    if(nearest.GetPosition().GetX() < robot.GetPosition().GetX())
    {
        return ACTION::LEFT;
    }
    // vertical movement
    if(nearest.GetPosition().GetY() > robot.GetPosition().GetY())
    {
        return ACTION::UP;
    }
    if(nearest.GetPosition().GetY() < robot.GetPosition().GetY())
    {
        return ACTION::DOWN;
    }
    return ACTION::NONE;
}

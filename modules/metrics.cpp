#include "metrics.hpp"

ACTION MetricsGetAction(const Robot &robot, const AsteroidMap &a)
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
    // if the robot is not full, move to the resource with the best metric
    Resource resource = a.GetResources().front();

    float metric = 0;
    for(const Resource &r : a.GetResources())
    {
        float m = r.GetAmount() / (1.0 + Distance(robot.GetPosition(), r.GetPosition()));
        if(metric < m) {
            metric = m;
            resource = r;
        }
    }

    // horizontal movement
    if(resource.GetPosition().GetX() > robot.GetPosition().GetX())
    {
        return ACTION::RIGHT;
    }
    if(resource.GetPosition().GetX() < robot.GetPosition().GetX())
    {
        return ACTION::LEFT;
    }
    // vertical movement
    if(resource.GetPosition().GetY() > robot.GetPosition().GetY())
    {
        return ACTION::UP;
    }
    if(resource.GetPosition().GetY() < robot.GetPosition().GetY())
    {
        return ACTION::DOWN;
    }
    return ACTION::NONE;
}

#include "biggest.hpp"

ACTION BiggestGetAction(const Robot &robot, const AsteroidMap &a)
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
    // if the robot is not full, move to the biggest resource
    Resource biggest = a.GetResources().front();

    for(const Resource &r : a.GetResources())
    {
        if(biggest.GetAmount() < r.GetAmount())
        {
            biggest = r;
        }
    }
    // get nearest from biggest
    for(const Resource &r : a.GetResources())
    {
        Point rp = r.GetPosition();
        Point bp = biggest.GetPosition();
        if(biggest.GetAmount() == r.GetAmount())
        {
            if(Distance(bp, rp) < Distance(bp, robot.GetPosition()))
            {
                biggest = r;
            }
        }
    }

    // horizontal movement
    if(biggest.GetPosition().GetX() > robot.GetPosition().GetX())
    {
        return ACTION::RIGHT;
    }
    if(biggest.GetPosition().GetX() < robot.GetPosition().GetX())
    {
        return ACTION::LEFT;
    }
    // vertical movement
    if(biggest.GetPosition().GetY() > robot.GetPosition().GetY())
    {
        return ACTION::UP;
    }
    if(biggest.GetPosition().GetY() < robot.GetPosition().GetY())
    {
        return ACTION::DOWN;
    }
    return ACTION::NONE;
}

#ifndef _ASTEROID_MAP_HPP_
#define _ASTEROID_MAP_HPP_

#include "base.hpp"
#include "resource.hpp"
#include "robot.hpp"

#include <vector>

class AsteroidMap {
    std::vector<Resource> resources;
    std::vector<Robot> robots;
    std::vector<Base> bases;
public:
    AsteroidMap(const std::vector<Resource>& r, const std::vector<Robot>& ro, const std::vector<Base>& b);
    AsteroidMap(const AsteroidMap& a);
    std::vector<Resource> GetResources() const;
    std::vector<Robot> GetRobots() const;
    std::vector<Base> GetBases() const;

    bool IsOnBase(const Robot& r) const;
    bool IsOnResource(const Robot& r) const;
    Base GetNearestBase(const Robot& r) const;
};

#endif
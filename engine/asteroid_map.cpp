#include "asteroid_map.hpp"

AsteroidMap::AsteroidMap(
    const std::vector<Resource>& r,
    const std::vector<Robot>& ro,
    const std::vector<Base>& b)
    : resources(r), robots(ro), bases(b) {}

AsteroidMap::AsteroidMap(const AsteroidMap& a)
    : resources(a.resources), robots(a.robots), bases(a.bases) {}

std::vector<Resource> AsteroidMap::GetResources() const {
    return resources;
}

std::vector<Robot> AsteroidMap::GetRobots() const {
    return robots;
}

std::vector<Base> AsteroidMap::GetBases() const {
    return bases;
}

bool AsteroidMap::IsOnBase(const Robot& r) const {
    for (const Base& b : bases) {
        if (b.GetPosition() == r.GetPosition()) {
            return true;
        }
    }
    return false;
}

bool AsteroidMap::IsOnResource(const Robot& r) const {
    for (const Resource& res : resources) {
        if (res.GetPosition() == r.GetPosition()) {
            return true;
        }
    }
    return false;
}

Base AsteroidMap::GetNearestBase(const Robot& r) const {
    Base nearest = bases[0];
    float minDistance = Distance(r.GetPosition(), bases[0].GetPosition());
    for (const Base& b : bases) {
        float distance = Distance(r.GetPosition(), b.GetPosition());
        if (distance < minDistance) {
            minDistance = distance;
            nearest = b;
        }
    }
    return nearest;
}

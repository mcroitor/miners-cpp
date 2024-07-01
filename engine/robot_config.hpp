#ifndef _ROBOT_CONFIG_HPP_
#define _ROBOT_CONFIG_HPP_

#include <string>

struct RobotConfig
{
    std::string name;
    float speed;
    size_t capacity;

    RobotConfig(std::string n, float s = 1., size_t c = 5)
        : name(n), speed(0.2 * s), capacity(10 * c) {}
};


#endif
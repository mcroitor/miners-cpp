#ifndef _GAME_ENGINE_HPP_
#define _GAME_ENGINE_HPP_

#include "definitions.hpp"
#include "resource.hpp"
#include "robot.hpp"
#include "base.hpp"

#include "../ui/picasso/picasso.hpp"

#include <vector>

class GameEngine {
    int width;
    int height;
    int pixelSize;
    int max_steps;
    std::vector<Resource> resources;
    std::vector<Robot> robots;
    std::vector<Base> bases;
    usm::graphics::Picasso picasso;

    bool IsOnBase(const Robot& Robot) const;
    bool IsOnResource(const Robot& Robot) const;

    void DrawScore(const std::vector<int>& Scores);
    void DrawStatus(int Step);
    void DrawResources();
    void DrawRobots();
    void DrawBases();
public:
    GameEngine(int, int, int);
    void Init();

    void SetResources(const std::vector<Resource>& Resources);
    void SetRobots(const std::vector<Robot>& Robots);
    void SetBases(const std::vector<Base>& Bases);

    void AddResource(const Resource&);
    void AddRobot(const Robot&);
    void AddBase(const Base&);

    void Start();
};

#endif

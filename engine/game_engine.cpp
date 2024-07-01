#include "asteroid_map.hpp"
#include "game_engine.hpp"

#include <chrono>
#include <iostream>
#include <thread>

GameEngine::GameEngine(int w, int h, int s)
    : width(w),
      height(h),
      pixelSize(20),
      picasso(
          w * 20 + 200, //
          h * 20 + 200, //
          "Miner Game"),
      max_steps(s)
{
}

void GameEngine::Init()
{
}

bool GameEngine::IsOnBase(const Robot &Robot) const
{
    // Check if the Robot is on a base
    for (auto &base : bases)
    {
        if (base.GetPosition() == Robot.GetPosition())
        {
            return true;
        }
    }
    return false;
}

bool GameEngine::IsOnResource(const Robot &Robot) const
{
    // Check if the Robot is on a resource
    for (auto &resource : resources)
    {
        if (resource.GetPosition() == Robot.GetPosition())
        {
            return true;
        }
    }
    return false;
}

void GameEngine::Start()
{
    // Start the game engine
    int step = 0;
    std::vector<int> scores(robots.size(), 0);

    while (step < max_steps)
    {
        step++;
        // Collect actions
        AsteroidMap map(resources, robots, bases);
        std::vector<ACTION> actions;
        for (auto &robot : robots)
        {
            actions.push_back(robot.GetAction(map));
        }

        // do move
        for (int i = 0; i < robots.size(); i++)
        {
            switch (actions[i])
            {
            case ACTION::UP:
            case ACTION::DOWN:
            case ACTION::LEFT:
            case ACTION::RIGHT:
                robots[i].Move(actions[i]);
                break;
            case ACTION::MINE:
                for (auto &resource : resources)
                {
                    if (robots[i].GetPosition() == resource.GetPosition())
                    {
                        robots[i].Mine();
                        resource.Mine();
                        break;
                    }
                }
                break;
            case ACTION::UNLOAD:
                if (IsOnBase(robots[i]))
                {
                    scores[i] += robots[i].GetAmount();
                    robots[i].Unload();
                }
                break;
            default:
                break;
            }
        }
        // Render the game view
        picasso.SetBackgroundColor({255, 255, 255});
        picasso.SetForegroundColor({255, 255, 255});
        picasso.Clear();

        DrawScore(scores);
        DrawStatus(step);
        DrawResources();
        DrawBases();
        DrawRobots();

        // pause 0.2 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    picasso.Show();
}

void GameEngine::SetResources(const std::vector<Resource> &Resources)
{
    resources = Resources;
}

void GameEngine::SetRobots(const std::vector<Robot> &Robots)
{
    robots = Robots;
}

void GameEngine::SetBases(const std::vector<Base> &Bases)
{
    bases = Bases;
}

void GameEngine::AddBase(const Base &base)
{
    bases.push_back(base);
}

void GameEngine::AddResource(const Resource &resource)
{
    resources.push_back(resource);
}

void GameEngine::AddRobot(const Robot &robot)
{
    robots.push_back(robot);
}

void GameEngine::DrawScore(const std::vector<int> &scores)
{
    picasso.SetFont("Consolas", 14);
    picasso.SetForegroundColor({0, 0, 0});
    picasso.SetBackgroundColor({255, 255, 255});
    for (int i = 0; i < robots.size(); i++)
    {
        picasso.DrawText(
            {pixelSize * width + 10, (10 + i) * pixelSize},
            "Robot " + std::to_string(i + 1) + " score: " + std::to_string(scores[i]));
    }
}

void GameEngine::DrawStatus(int step)
{
    picasso.SetFont("Consolas", 14);
    usm::graphics::Color textColor{0, 0, 0};
    picasso.SetBackgroundColor({255, 255, 255});
    picasso.SetForegroundColor(textColor);
    picasso.DrawText(
        {pixelSize * width + 10, 10},
        "Step: " + std::to_string(step) + "/" + std::to_string(max_steps));
    // draw current amount
    for (int i = 0; i < robots.size(); i++)
    {
        picasso.DrawText(
            {pixelSize * width + 10, (2 + i) * pixelSize},
            "Robot " + std::to_string(i + 1) + " amount: " + std::to_string(robots[i].GetAmount()));
    }
}

void GameEngine::DrawResources()
{
    usm::graphics::Color resBgColor{255, 255, 255};
    usm::graphics::Color resColor{127, 127, 255};
    usm::graphics::Color resEmptyColor{127, 127, 127};
    picasso.SetBackgroundColor(resBgColor);
    for (auto &resource : resources)
    {
        if (resource.GetAmount() > 0)
        {
            picasso.SetForegroundColor(resColor);
        }
        else
        {
            picasso.SetForegroundColor(resEmptyColor);
        }
        picasso.FillRectangle(
            {pixelSize * resource.GetPosition().GetX(),
             pixelSize * resource.GetPosition().GetY()},
            {pixelSize * resource.GetPosition().GetX() + pixelSize,
             pixelSize * resource.GetPosition().GetY() + pixelSize});
    }
}

void GameEngine::DrawRobots()
{
    usm::graphics::Color robotBgColor{0, 0, 127};
    usm::graphics::Color robotColor{0, 0, 127};
    picasso.SetBackgroundColor(robotBgColor);
    picasso.SetForegroundColor(robotColor);
    for (int i = 0; i < robots.size(); i++)
    {
        picasso.FillCircle(
            {pixelSize * robots[i].GetPosition().GetX() + pixelSize / 2,
             pixelSize * robots[i].GetPosition().GetY() + pixelSize / 2},
            pixelSize / 2);
    }
}

void GameEngine::DrawBases()
{
    usm::graphics::Color baseBgColor{255, 255, 255};
    usm::graphics::Color baseColor{255, 0, 0};
    picasso.SetBackgroundColor(baseBgColor);
    picasso.SetForegroundColor(baseColor);
    for (auto &base : bases)
    {
        picasso.FillCircle(
            {pixelSize * base.GetPosition().GetX() + pixelSize / 2,
             pixelSize * base.GetPosition().GetY() + pixelSize / 2},
            pixelSize / 2);
    }
}

#include "engine/game_engine.hpp"
#include "modules/biggest.hpp"
#include "modules/metrics.hpp"
#include "modules/nearest.hpp"
#include "modules/minsum.hpp"

#include <chrono>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(1, 50);

int main()
{
    int width = 30;
    int height = 20;
    GameEngine game(width, height, 500);

    game.SetBases({
        Base({distrib(gen) % width, distrib(gen) % height}),
        Base({distrib(gen) % width, distrib(gen) % height}),
        Base({distrib(gen) % width, distrib(gen) % height}),
    });

    for (int i = 0; i < 20; ++i)
    {
        game.AddResource(
            Resource(
                {distrib(gen) % 30, distrib(gen) % 20},
                distrib(gen)));
    }

    game.SetRobots({
        Robot({"R1 Nearest", 5., 1}, {1, 1}, NearestGetAction),
        Robot({"R2 Nearest", 3., 3}, {1, 1}, NearestGetAction),
        Robot({"R3 Min Sum", 3., 3}, {1, 1}, MinSumGetAction),
        Robot({"R4 Biggest", 5., 1}, {1, 1}, BiggestGetAction),
        Robot({"R5 Metrics", 2., 4}, {1, 1}, MetricsGetAction),
        Robot({"R6 Min Sum", 4., 2}, {1, 1}, MinSumGetAction),
    });

    game.Init();
    game.Start();
    return 0;
}

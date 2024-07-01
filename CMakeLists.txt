# cmake version 3.0 or later
cmake_minimum_required(VERSION 3.20)

# project name
project(Miners)

# set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# set include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules)

set(SOURCES main.cpp
    engine/asteroid_map.cpp
    engine/base.cpp
    engine/game_engine.cpp
    engine/point.cpp
    engine/resource.cpp
    engine/robot.cpp
    modules/biggest.cpp
    modules/metrics.cpp
    modules/nearest.cpp
    modules/minsum.cpp
    ui/picasso/color.cpp
    ui/picasso/point.cpp
    ui/picasso/picasso.cpp)

# add the executable
add_executable(Miners WIN32 ${SOURCES})
target_link_libraries(Miners gdi32)

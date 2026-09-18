#pragma once
#include <vector>
#include "platform/platform.hpp"

struct World{
    World(float leftBound, float rightBound, float groundY);
    
    float leftBound;
    float rightBound;
    float groundY;
    std::vector<Platform> platforms;
};
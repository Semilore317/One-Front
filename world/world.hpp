#pragma once
#include "platform/platform.hpp"
#include <vector>

struct World {
	World(float rightBound, float groundY);

	float leftBound;
	float rightBound;
	float groundY;
	std::vector<Platform> platforms;
};
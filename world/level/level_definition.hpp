#pragma once

#include "../platform/platform.hpp"
#include "raylib.h"
#include <vector>

struct LevelDefinition {
	float leftBound;
	float rightBound;
	float topBound;
	float groundY;
	Vector2 playerSpawn;
	std::vector<Platform> platforms;
};

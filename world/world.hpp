#pragma once

#include "level/level_definition.hpp"
#include "platform/platform.hpp"
#include <vector>

struct World {
	explicit World(const LevelDefinition &level);
	World(float leftBound,
	      float rightBound,
	      float topBound,
	      float groundY,
	      std::vector<Platform> platforms = {});

	float leftBound;
	float rightBound;
	float topBound;
	float groundY;
	std::vector<Platform> platforms;

	void update(float deltaTime);
};

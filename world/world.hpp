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
	      std::vector<Platform> platforms = {},
	      Rectangle goal = {});

	float leftBound;
	float rightBound;
	float topBound;
	float groundY;
	Rectangle goal;
	std::vector<Platform> platforms;

	void update(float deltaTime);
};

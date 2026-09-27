#pragma once
#include "platform/platform.hpp"
#include <vector>

struct World {
	World(float leftBound,
	      float rightBound,
	      float topBound,
	      float groundY,
	      std::vector<Platform> platforms = {});

	[[nodiscard]] static World vertical_prototype(float rightBound,
	                                              float groundY);

	float leftBound;
	float rightBound;
	float topBound;
	float groundY;
	std::vector<Platform> platforms;

	void update(float deltaTime);
};

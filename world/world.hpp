#pragma once

#include "platform/platform.hpp"
#include "training_dummy/training_dummy.hpp"
#include <vector>

struct World {
	World(float leftBound,
	      float rightBound,
	      float topBound,
	      float groundY,
	      std::vector<Platform> platforms = {},
	      TrainingDummy trainingDummy = {});

	[[nodiscard]] static World vertical_prototype(float rightBound,
	                                              float groundY);

	float leftBound;
	float rightBound;
	float topBound;
	float groundY;
	std::vector<Platform> platforms;
	TrainingDummy trainingDummy;

	void update(float deltaTime);
};

#include "./world.hpp"

#include <utility>

World::World(const LevelDefinition &level):
    World{level.leftBound,
          level.rightBound,
          level.topBound,
          level.groundY,
          level.platforms,
          level.goal} {}

World::World(float leftBound,
             float rightBound,
             float topBound,
             float groundY,
             std::vector<Platform> platforms,
             Rectangle goal):
    leftBound(leftBound),
    rightBound(rightBound),
    topBound(topBound),
    groundY(groundY),
    goal(goal),
    platforms(std::move(platforms)) {}

void World::update(float deltaTime) {
	for (Platform &platform : platforms) {
		platform.update(deltaTime);
	}
}

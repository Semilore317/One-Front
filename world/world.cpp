#include "./world.hpp"

#include <utility>

World::World(const LevelDefinition &level):
    World{level.leftBound,
          level.rightBound,
          level.topBound,
          level.groundY,
          level.platforms} {}

World::World(float leftBound,
             float rightBound,
             float topBound,
             float groundY,
             std::vector<Platform> platforms):
    leftBound(leftBound),
    rightBound(rightBound),
    topBound(topBound),
    groundY(groundY),
    platforms(std::move(platforms)) {}

void World::update(float deltaTime) {
	for (Platform &platform : platforms) {
		platform.update(deltaTime);
	}
}

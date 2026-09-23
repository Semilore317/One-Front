#include "./world.hpp"

constexpr float PLATFORM_HEIGHT = 15.0f;
constexpr float PLATFORM_WIDTH = 180.0f;

World::World(float rightBound, float groundY):
    leftBound(0),
    rightBound(rightBound),
    groundY(groundY),
    // prototype platform layout in world-space coordinates
    platforms({
        {{120, 580}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},
        {{360, 550},
         {PLATFORM_WIDTH, PLATFORM_HEIGHT},
         true,
         360.0f,
         600.0f,
         100.0f},
        {{650, 500}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},
        {{920, 500}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},
    }) {}

void World::update(float deltaTime) {
	for (Platform &platform : platforms) {
		platform.update(deltaTime);
	}
}

#include "./world.hpp"

constexpr float PLATFORM_HEIGHT = 15.0f;
constexpr float PLATFORM_WIDTH = 180.0f;

World::World(float rightBound, float groundY):
    leftBound(0),
    rightBound(rightBound),
    groundY(groundY),
    // prototype platform layout in world-space coordinates
    platforms({
        {{80, 580}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},
        {{340, 525}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},

        // first trap ledge
        {{650, 470}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},
        {{650, 410}, {30, 60}, true, 650.0f, 800.0f, 130.0f},
        {{960, 415}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},

        // moving bridge
        {{720, 360},
         {PLATFORM_WIDTH, PLATFORM_HEIGHT},
         true,
         620.0f,
         850.0f,
         140.0f},

        // low-ceiling conveyor trap
        {{250, 500},
         {PLATFORM_WIDTH, PLATFORM_HEIGHT},
         true,
         250.0f,
         800.0f,
         160.0f},
        {{520, 440}, {260, PLATFORM_HEIGHT}},

        // second trap ledge
        {{470, 305}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},
        {{470, 245}, {30, 60}, true, 470.0f, 620.0f, 180.0f},
        {{180, 250}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},

        // upper moving platform
        {{400, 195},
         {PLATFORM_WIDTH, PLATFORM_HEIGHT},
         true,
         350.0f,
         700.0f,
         180.0f},

        {{760, 140}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},
        {{1040, 85}, {PLATFORM_WIDTH, PLATFORM_HEIGHT}},
    }) {}

void World::update(float deltaTime) {
	for (Platform &platform : platforms) {
		platform.update(deltaTime);
	}
}

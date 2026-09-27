#include "game_camera.hpp"

#include "../../world/player/player.hpp"
#include "../../world/world.hpp"
#include <algorithm>
#include <cmath>

namespace {
constexpr float CAMERA_FOLLOW_SPEED{6.0f};

float bounded_axis_target(float desiredTarget,
                          float minimum,
                          float maximum,
                          float halfViewportSize) {
	const float worldSize = maximum - minimum;
	if (worldSize <= halfViewportSize * 2.0f)
		return minimum + worldSize * 0.5f;

	return std::clamp(
	    desiredTarget, minimum + halfViewportSize, maximum - halfViewportSize);
}
} // namespace

GameCamera::GameCamera(float viewportWidth,
                       float viewportHeight,
                       const Player &player,
                       const World &world):
    camera{},
    viewportWidth{viewportWidth},
    viewportHeight{viewportHeight} {
	camera.offset = {viewportWidth * 0.5f, viewportHeight * 0.5f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	camera.target = bounded_target(player, world);
}

void GameCamera::update(float deltaTime,
                        const Player &player,
                        const World &world) {
	const Vector2 desiredTarget = bounded_target(player, world);
	const float interpolation =
	    1.0f - std::exp(-CAMERA_FOLLOW_SPEED * deltaTime);

	camera.target.x += (desiredTarget.x - camera.target.x) * interpolation;
	camera.target.y += (desiredTarget.y - camera.target.y) * interpolation;
}

Vector2 GameCamera::bounded_target(const Player &player,
                                   const World &world) const {
	const Vector2 playerCenter{
	    player.position.x + player.size.x * 0.5f,
	    player.position.y + player.size.y * 0.5f,
	};

	const float halfViewportWidth = viewportWidth * 0.5f / camera.zoom;
	const float halfViewportHeight = viewportHeight * 0.5f / camera.zoom;

	return {
	    bounded_axis_target(playerCenter.x,
		                    world.leftBound,
		                    world.rightBound,
		                    halfViewportWidth),
	    bounded_axis_target(
	        playerCenter.y, world.topBound, world.groundY, halfViewportHeight),
	};
}

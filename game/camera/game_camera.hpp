#pragma once

#include "raylib.h"

struct Player;
struct World;

struct GameCamera {
	GameCamera(float viewportWidth,
	           float viewportHeight,
	           const Player &player,
	           const World &world);

	Camera2D camera;

	void update(float deltaTime, const Player &player, const World &world);

  private:
	float viewportWidth;
	float viewportHeight;

	[[nodiscard]]
	Vector2 bounded_target(const Player &player, const World &world) const;
};

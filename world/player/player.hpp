#pragma once

#include "./../../game/controls.hpp"
#include "./../platform/platform.hpp"
#include "raylib.h"
#include <vector>

enum class Facing { Left, Right };

struct Player {
	Player();
	Player(Vector2 position, Vector2 size);

	Vector2 position;
	Vector2 velocity;
	Vector2 size;

	Facing facing;
	bool isGrounded;
	bool isCrouching;

	bool isAttacking;
	float attackTimeRemaining;
	float attackCooldownRemaining;

	float maxHealth;
	float currentHealth;

	[[nodiscard]]
	Rectangle attack_hitbox() const;
	void update(float deltaTime,
	            const Controls &controls,
	            float groundY,
	            float leftBound,
	            float rightBound,
	            const std::vector<Platform> &platforms);

  private:
	float standingHeight;

	void update_crouch(const Controls &controls,
	                   const std::vector<Platform> &platforms);
	void crouch();
	void stand_up();
	bool can_stand(const std::vector<Platform> &platforms) const;

	// Platforming Helpers
	void apply_gravity(float deltaTime);
	void apply_fast_fall(const Controls &controls);
	[[nodiscard]]
	bool is_on_surface(float groundY,
	                   const std::vector<Platform> &platforms) const;
	void handle_platform_landing(float previousBottom,
	                             float currentBottom,
	                             const std::vector<Platform> &platforms);
	void handle_platform_horizontal_collision(
	    float previousX, const std::vector<Platform> &platforms);
	void
	handle_platform_underside_collision(float previousTop,
	                                    float currentTop,
	                                    const std::vector<Platform> &platforms);
	bool overlaps_horizontally(const Platform &platform) const;
	bool overlaps_vertically(const Platform &platform) const;
	void apply_platform_movement(const std::vector<Platform> &platforms);

	// Combat Helpers
	void update_attack(float deltaTime, const Controls &controls);
};

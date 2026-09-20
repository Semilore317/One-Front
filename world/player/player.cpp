#include "player.hpp"
#include "raylib.h"
#include <algorithm>
#include <vector>

// Player stats
constexpr float DEFAULT_MAX_HEALTH = 100.0f;

// Movement
constexpr float DEFAULT_MOVE_SPEED = 400.0f; // 400px per second
constexpr float GRAVITY = 600.0f;
constexpr float JUMP_SPEED = 300.0f;

// Combat
constexpr float ATTACK_DURATION = 0.2f;
constexpr float ATTACK_COOLDOWN = 0.5f;
constexpr float ATTACK_RANGE = 25.0f; 

Player::Player():
    position{0,0},
    velocity{0,0},
    size{1,1},
    facing{Facing::Right},
    isGrounded{true},
    isAttacking{false},
    attackTimeRemaining{0.0f},
    attackCooldownRemaining{0.0f},
    maxHealth{DEFAULT_MAX_HEALTH},
    currentHealth{DEFAULT_MAX_HEALTH} {}

Player::Player(Vector2 position, Vector2 size):
    position{position},
    velocity{0,0},
    size{size},
    facing{Facing::Right},
    isGrounded{true},
    isAttacking{false},
    attackTimeRemaining{0.0f},
    attackCooldownRemaining{0.0f},
    maxHealth{DEFAULT_MAX_HEALTH},
    currentHealth{DEFAULT_MAX_HEALTH} {}

void Player::update(float deltaTime,
                    const Controls &controls,
                    float groundY,
                    float leftBound,
                    float rightBound,
                    const std::vector<Platform> &platforms) {

	// horizontal movement
	if (IsKeyDown(controls.left)) {
		velocity.x = -DEFAULT_MOVE_SPEED;
		facing = Facing::Left;
	} else if (IsKeyDown(controls.right)) {
		velocity.x = DEFAULT_MOVE_SPEED;
		facing = Facing::Right;
	} else
		velocity.x = 0;

	float previousX = position.x;

	position.x += velocity.x * deltaTime;
	position.x = std::clamp(position.x, leftBound, rightBound - size.x);
	handle_platform_horizontal_collision(previousX, platforms);

	// is the avatar standing on something?
	isGrounded = is_on_surface(groundY, platforms);

	// jumping
	if (IsKeyPressed(controls.jump) && isGrounded) {
		velocity.y = -JUMP_SPEED;
		isGrounded = false;
	}

	// gravity
	if (!isGrounded)
		apply_gravity(deltaTime);

	float previousTop = position.y;
	float previousBottom = position.y + size.y;

	position.y += velocity.y * deltaTime;

	float currentTop = position.y;
	float currentBottom = position.y + size.y;

	// platform logic
	handle_platform_underside_collision(previousTop, currentTop, platforms);
	handle_platform_landing(previousBottom, currentBottom, platforms);

	// ground landing
	if (position.y + size.y >= groundY) {
		position.y = groundY - size.y;
		velocity.y = 0;
		isGrounded = true;
	}
}

/* Private Methods */

void Player::apply_gravity(float deltaTime) {
	velocity.y += GRAVITY * deltaTime;
}

bool Player::is_on_surface(float groundY,
                           const std::vector<Platform> &platforms) const {
	// check whether we're still standing on a surface
	bool supported = position.y + size.y >= groundY;

	for (const Platform &platform : platforms) {
		bool onPlatformTop = position.y + size.y == platform.top();

		if (onPlatformTop && overlaps_horizontally(platform)) {
			supported = true;
			break;
		}
	}
	return supported;
}

void Player::handle_platform_landing(float previousBottom,
                                     float currentBottom,
                                     const std::vector<Platform> &platforms) {
	for (const Platform &platform : platforms) {
		bool isFalling = velocity.y > 0;
		bool crossedPlatformTop =
		    previousBottom <= platform.top() && currentBottom >= platform.top();

		if (isFalling && crossedPlatformTop &&
		    overlaps_horizontally(platform)) {
			position.y = platform.top() - size.y;
			velocity.y = 0;
			isGrounded = true;
			break;
		}
	}
}

void Player::handle_platform_horizontal_collision(
    float previousX, const std::vector<Platform> &platforms) {
	for (const Platform &platform : platforms) {
		float previousLeft = previousX;
		float previousRight = previousLeft + size.x;

		float currentRight = position.x + size.x;
		float currentLeft = position.x;

		if (!overlaps_vertically(platform))
			continue;

		// moving right into platform's left side
		if (velocity.x > 0 && previousRight <= platform.left() &&
		    currentRight >= platform.left()) {
			position.x = platform.left() - size.x;
			velocity.x = 0;
			break;
		}

		// moving left into platform's right side
		if (velocity.x < 0 && previousLeft >= platform.right() &&
		    currentLeft <= platform.right()) {
			position.x = platform.right();
			velocity.x = 0;
			break;
		}
	}
}

void Player::handle_platform_underside_collision(
    float previousTop,
    float currentTop,
    const std::vector<Platform> &platforms) {
	for (const Platform &platform : platforms) {
		bool isRising = velocity.y < 0;

		bool crossedPlatformBottom =
		    previousTop >= platform.bottom() && currentTop <= platform.bottom();

		if (isRising && crossedPlatformBottom &&
		    overlaps_horizontally(platform)) {
			position.y = platform.bottom();
			velocity.y = 0;
			break;
		}
	}
}

bool Player::overlaps_horizontally(const Platform &platform) const {
	return position.x + size.x > platform.left() &&
	       position.x < platform.right();
}

bool Player::overlaps_vertically(const Platform &platform) const {
	return position.y + size.y > platform.top() &&
	       position.y < platform.bottom();
}

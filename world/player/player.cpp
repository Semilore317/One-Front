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
constexpr float ATTACK_REACH = 25.0f;
constexpr float ATTACK_THICKNESS = 20.0f;

// Crouching
constexpr float CROUCH_HEIGHT_RATIO = 0.6f;

Player::Player():
    position{0, 0},
    velocity{0, 0},
    size{1, 1},
    facing{Facing::Right},
    isGrounded{true},
    isCrouching{false},
    isAttacking{false},
    attackTimeRemaining{0.0f},
    attackCooldownRemaining{0.0f},
    maxHealth{DEFAULT_MAX_HEALTH},
    currentHealth{DEFAULT_MAX_HEALTH},
    standingHeight{1.0f} {}

Player::Player(Vector2 position, Vector2 size):
    position{position},
    velocity{0, 0},
    size{size},
    facing{Facing::Right},
    isGrounded{true},
    isCrouching{false},
    isAttacking{false},
    attackTimeRemaining{0.0f},
    attackCooldownRemaining{0.0f},
    maxHealth{DEFAULT_MAX_HEALTH},
    currentHealth{DEFAULT_MAX_HEALTH},
    standingHeight{size.y} {}

// clang-format off
Rectangle Player::attack_hitbox() const {
	const float hitBoxX =
	    facing == Facing::Right
					? position.x + size.x
					: position.x - size.x;

	const float hitBoxY = position.y + (size.y - ATTACK_THICKNESS) * 0.5f;

	return {
		hitBoxX,
		hitBoxY,
		ATTACK_THICKNESS,
		size.y - ATTACK_THICKNESS
	};
}
// clang-format on

void Player::update(float deltaTime,
                    const Controls &controls,
                    float groundY,
                    float leftBound,
                    float rightBound,
                    const std::vector<Platform> &platforms) {
	update_attack(deltaTime, controls);

	const float previousX = position.x;

	// inherit movement from a moving platform
	apply_platform_movement(platforms);

	// horizontal movement
	if (IsKeyDown(controls.left)) {
		velocity.x = -DEFAULT_MOVE_SPEED;
		facing = Facing::Left;
	} else if (IsKeyDown(controls.right)) {
		velocity.x = DEFAULT_MOVE_SPEED;
		facing = Facing::Right;
	} else
		velocity.x = 0;

	position.x += velocity.x * deltaTime;
	position.x = std::clamp(position.x, leftBound, rightBound - size.x);

	handle_platform_horizontal_collision(previousX, platforms);
	position.x = std::clamp(position.x, leftBound, rightBound - size.x);

	// is the avatar standing on something?
	isGrounded = is_on_surface(groundY, platforms);

	update_crouch(controls, platforms);

	// jumping
	if (IsKeyPressed(controls.jump) && isGrounded && !isCrouching) {
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

/* Private Helpers*/

/* Crouch Helpers*/
void Player::update_crouch(const Controls &controls,
                           const std::vector<Platform> &platforms) {
	if (!isGrounded) {
		if (isCrouching && can_stand(platforms))
			stand_up();
		return;
	}

	if (IsKeyDown(controls.down)) {
		crouch();
		return;
	}

	if (isCrouching && can_stand(platforms))
		stand_up();

}
void Player::crouch() {
	if (isCrouching)
		return;

	const float crouchHeight = standingHeight * CROUCH_HEIGHT_RATIO;
	const float heightDifference = size.y - crouchHeight;

	position.y += heightDifference;
	size.y = crouchHeight;
	isCrouching = true;
}

void Player::stand_up() {
	if (!isCrouching)
		return;

	const float heightDifference = standingHeight - size.y;

	position.y -= heightDifference;
	size.y = standingHeight;
	isCrouching = false;
}

bool Player::can_stand(const std::vector<Platform> &platforms) const {
	const float standingTop = position.y - (standingHeight - size.y);
	const float standingBottom = position.y + size.y;

	for (const Platform &platform : platforms) {
		const bool overlapsHorizontally =
		    position.x + size.x > platform.left() &&
		    position.x < platform.right();

		const bool overlapsVertically =
		    standingBottom > platform.top() && standingTop < platform.bottom();

		if (overlapsHorizontally && overlapsVertically)
			return false;
	}

	return true;
}

/* Platforming Helpers */
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
	const float previousPlayerLeft = previousX;
	const float previousPlayerRight = previousX + size.x;

	const float currentPlayerLeft = position.x;
	const float currentPlayerRight = position.x + size.x;

	const float playerMovement = position.x - previousX;

	for (const Platform &platform : platforms) {
		if (!overlaps_vertically(platform))
			continue;

		const float platformMovement = platform.movementDelta.x;

		const float previousPlatformLeft = platform.left() - platformMovement;
		const float previousPlatformRight = platform.right() - platformMovement;

		const float relativeMovement = playerMovement - platformMovement;

		const bool overlapsNow = currentPlayerRight > platform.left() &&
		                         currentPlayerLeft < platform.right();

		const bool crossedLeftEdge =
		    previousPlayerRight <= previousPlatformLeft &&
		    currentPlayerRight >= platform.left();

		const bool crossedRightEdge =
		    previousPlayerLeft >= previousPlatformRight &&
		    currentPlayerLeft <= platform.right();

		// approaching platform's left side
		if (relativeMovement > 0.0f && (crossedLeftEdge || overlapsNow)) {
			position.x = platform.left() - size.x;
			velocity.x = 0.0f;
			break;
		}

		// approaching platform's right side
		if (relativeMovement < 0.0f && (crossedRightEdge || overlapsNow)) {
			position.x = platform.right();
			velocity.x = 0.0f;
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

void Player::apply_platform_movement(const std::vector<Platform> &platforms) {
	for (const Platform &platform : platforms) {
		if (platform.movementDelta.x == 0.0f)
			continue;

		const float previousLeft = platform.left() - platform.movementDelta.x;
		const float previousRight = platform.right() - platform.movementDelta.x;
		const bool wasOnPlatform = position.y + size.y == platform.top();
		const bool overlappedPreviously =
		    position.x + size.x > previousLeft && position.x < previousRight;
		if (wasOnPlatform && overlappedPreviously) {
			position.x += platform.movementDelta.x;
			break;
		}
	}
}

/* Combat Helpers */
void Player::update_attack(float deltaTime, const Controls &controls) {
	attackTimeRemaining = std::max(0.0f, attackTimeRemaining - deltaTime);
	attackCooldownRemaining =
	    std::max(0.0f, attackCooldownRemaining - deltaTime);

	isAttacking = attackTimeRemaining > 0;

	if (IsKeyPressed(controls.attack1) && attackCooldownRemaining == 0.0f) {
		attackTimeRemaining = ATTACK_DURATION;
		attackCooldownRemaining = ATTACK_COOLDOWN;
		isAttacking = true;
	}
}

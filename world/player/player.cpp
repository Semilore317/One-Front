#include "player.hpp"
#include "raylib.h"
#include <algorithm>
#include <vector>

constexpr float DEFAULT_MOVE_SPEED = 400.0f; // 400px per second
constexpr float GRAVITY = 600.0f;
constexpr float JUMP_SPEED = 300.0f;

Player::Player()
    : isGrounded{true}, position{0, 0}, velocity{0, 0}, size{1, 1} {}

Player::Player(Vector2 position, Vector2 size)
    : isGrounded{true}, position{position}, velocity{0, 0}, size{size} {}

void Player::update(float deltaTime, const Controls &controls, float groundY,
                    float leftBound, float rightBound,
                    const std::vector<Platform> &platforms) {

  // horizontal movement
  if (IsKeyDown(controls.left))
    velocity.x = -DEFAULT_MOVE_SPEED;
  else if (IsKeyDown(controls.right))
    velocity.x = DEFAULT_MOVE_SPEED;
  else
    velocity.x = 0;

  position.x += velocity.x * deltaTime;
  position.x = std::clamp(position.x, leftBound, rightBound - size.x);

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

  float previousBottom = position.y + size.y;

  position.y += velocity.y * deltaTime;

  float currentBottom = position.y + size.y;

  // platform landing
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
    bool onPlatformTop = position.y + size.y == platform.position.y;

    bool overlapsHorizontally =
        position.x + size.x > platform.position.x &&
        position.x < platform.position.x + platform.size.x;

    if (onPlatformTop && overlapsHorizontally) {
      supported = true;
      break;
    }
  }

  return supported;
}

void Player::handle_platform_landing(float previousBottom, float currentBottom,
                                     const std::vector<Platform> &platforms) {
  for (const Platform &platform : platforms) {
    float platformTop = platform.position.y;

    bool isFalling = velocity.y > 0;
    bool crossedPlatformTop =
        previousBottom <= platformTop && currentBottom >= platformTop;
    bool overlapsHorizontally =
        position.x + size.x > platform.position.x &&
        position.x < platform.position.x + platform.size.x;

    if (isFalling && crossedPlatformTop && overlapsHorizontally) {
      position.y = platform.position.y - size.y;
      velocity.y = 0;
      isGrounded = true;
      break;
    }
  }
}

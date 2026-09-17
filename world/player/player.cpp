#include "player.hpp"
#include "raylib.h"
#include <algorithm>

constexpr float DEFAULT_MOVE_SPEED = 400.0f; // 400px per second
constexpr float GRAVITY = 600.0f;
constexpr float JUMP_SPEED = 250.0f;

Player::Player():
    isGrounded{true},
    position{0, 0},
    velocity{0, 0},
    size{1, 1} {}

Player::Player(Vector2 position, Vector2 size):
    isGrounded{true},
    position{position},
    velocity{0, 0},
    size{size} {}

void Player::update(
    float deltaTime, 
    const Controls& controls, 
    float groundY, 
    float leftBound, 
    float rightBound) {
        
  // horizontal movement
  if(IsKeyDown(controls.left))
      velocity.x = -DEFAULT_MOVE_SPEED;
  else if(IsKeyDown(controls.right))
      velocity.x = DEFAULT_MOVE_SPEED;
  else
      velocity.x = 0;

  if(IsKeyPressed(controls.jump) && isGrounded){
      velocity.y = -JUMP_SPEED;
      isGrounded = false;
  }

  // if airborne
  // apply gravity
  if(!isGrounded)
      apply_gravity(deltaTime);

  position.x += velocity.x * deltaTime;
  // the valid range for x is:
  // leftBound <= position.x <= rightBound - avatar width
  position.x = std::clamp(position.x, leftBound, rightBound - size.x);
  
  position.y += velocity.y * deltaTime;

  // check whether the bottom of the avatar has hit the ground
  if(position.y + size.y >= groundY){
      position.y = groundY - size.y;
      velocity.y = 0;
      isGrounded = true;
  }
}

void Player::apply_gravity(float deltaTime) {
    velocity.y += GRAVITY * deltaTime;
}
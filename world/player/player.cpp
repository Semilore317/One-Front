#include "player.hpp"

constexpr float DEFAULT_MOVE_SPEED = 200.0f; // 200px per second

Player::Player(): 
    position{0, 0}, 
    velocity{0, 0}, 
    size{1, 1} {}

Player::Player(Vector2 position, Vector2 size): 
    position{position}, 
    velocity{0, 0}, 
    size{size} {}


void Player::update(float deltaTime, const Controls& controls) {
  // locomotion lives here

  // TODO: JUMP & GRAVITY
  // pressing up is a jump and i haven't fully thought it out yet.
  // would require a gravity mechanism

  if(IsKeyDown(controls.left))
      velocity.x = -DEFAULT_MOVE_SPEED;
  else if(IsKeyDown(controls.right))
      velocity.x = DEFAULT_MOVE_SPEED;
  else
      velocity.x = 0;

  position.x += velocity.x * deltaTime;
}

void Player::draw() const{
  // drawing goes here
  DrawRectangleV(position, size, RED);
}

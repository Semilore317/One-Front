#pragma once

#include "./../../game/controls.hpp"
#include "raylib.h"


struct Player {
  Player();
  Player(Vector2 position, Vector2 size);

  bool isGrounded;
  Vector2 position;
  Vector2 velocity;
  Vector2 size;

  void update(float deltaTime, const Controls &controls, float groundY);

private:
  void apply_gravity(float deltaTime);
};

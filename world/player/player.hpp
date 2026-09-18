#pragma once

#include "./../../game/controls.hpp"
#include "./../platform/platform.hpp"
#include "raylib.h"
#include <vector>

struct Player {
  Player();
  Player(Vector2 position, Vector2 size);

  bool isGrounded;
  Vector2 position;
  Vector2 velocity;
  Vector2 size;

  void update(float deltaTime, const Controls &controls, float groundY,
              float leftBound, float rightBound,
              const std::vector<Platform> &platforms);

private:
  void apply_gravity(float deltaTime);
  bool is_on_surface(float groundY, const std::vector<Platform> &platforms) const;
  void handle_platform_landing(float previousBottom, float currentBottom,
                          const std::vector<Platform> &platforms);
};

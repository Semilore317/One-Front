#pragma once

#include "./../../game/controls.hpp"
#include "./../platform/platform.hpp"
#include "raylib.h"
#include <vector>

enum class Facing { Left, Right };

struct Player {
  Player();
  Player(Vector2 position, Vector2 size);

  Facing facing;
  bool isGrounded;
  Vector2 position;
  Vector2 velocity;
  Vector2 size;

  void update(float deltaTime, const Controls &controls, float groundY,
              float leftBound, float rightBound,
              const std::vector<Platform> &platforms);
  void draw_player(const Player &player);

  float max_health = 100.0f;
  float current_health = 50.0f;

private:
  void apply_gravity(float deltaTime);
  bool is_on_surface(float groundY,
                     const std::vector<Platform> &platforms) const;
  void handle_platform_landing(float previousBottom, float currentBottom,
                               const std::vector<Platform> &platforms);
  void
  handle_platform_horizontal_collision(float previousX,
                                       const std::vector<Platform> &platforms);
  void
  handle_platform_underside_collision(float previousTop, float currentTop,
                                      const std::vector<Platform> &platforms);
  bool overlaps_horizontally(const Platform &platform) const;
  bool overlaps_vertically(const Platform &platform) const;
};

#pragma once

#include "raylib.h"

struct Player {
  Vector2 position;
  Vector2 velocity;
  Vector2 size;
};

Player create_player(Vector2 position, Vector2 size);
void update_player(Player &player, float deltaTime);
void draw_pixel(const Player &player);

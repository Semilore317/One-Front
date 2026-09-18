#include "draw_player.hpp"
#include <raylib.h>

void draw_player(const Player &player) {
  // Grab the coordinates to make the code cleaner.
  float px = player.position.x;
  float py = player.position.y;

  // Draw stick figure relative to the position (px,py).
  // Head
  DrawCircle(px, py - 40, 10, WHITE);

  // Body (neck to waist)
  DrawLine(px, py - 30, px, py - 10, WHITE);

  // Legs
  DrawLine(px, py - 10, px - 15, py + 10, WHITE); // Left Leg
  DrawLine(px, py - 10, px + 15, py + 10, WHITE); // Right Leg

  // Arms
  DrawLine(px, py - 25, px - 15, py - 15, WHITE); // Left arm
  DrawLine(px, py - 25, px + 15, py - 15, WHITE); // Riht arm.
}

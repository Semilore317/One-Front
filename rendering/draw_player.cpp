#include "draw_player.hpp"

#include <algorithm>
#include <raylib.h>

void draw_player(const Player &player) {
  /*  // Grab the coordinates to make the code cleaner.
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
    */

  const float x = player.position.x;
  const float y = player.position.y;
  const float width = player.size.x;
  const float height = player.size.y;

  const float centerX = x + width * 0.5f;
  const float headRadius = std::min(width * 0.25f, height * 0.15f);

  const Vector2 head{centerX, y + headRadius};
  const Vector2 neck{centerX, y + headRadius * 2.0f};
  const Vector2 shoulders{centerX, y + height * 0.4f};
  const Vector2 hips{centerX, y + height * 0.65f};

  const Vector2 leftHand{x + width * 0.1f, y + height * 0.6f};

  const Vector2 rightHand{x + width * 0.9f, y + height * 0.6f};

  const Vector2 leftFoot{x + width * 0.1f, y + height};

  const Vector2 rightFoot{x + width * 0.9f, y + height};

  DrawCircleV(head, headRadius, WHITE);
  DrawLineV(neck, hips, WHITE);
  DrawLineV(hips, rightFoot, WHITE);
  DrawLineV(hips, leftFoot, WHITE);
  DrawLineV(shoulders, leftHand, WHITE);
  DrawLineV(shoulders, rightHand, WHITE);

  // show the directiotn the player is facing.
  const float direction = player.facing == Facing::Right ? 1.0f : -1.0f;

  const Vector2 eye{
      head.x + direction * headRadius * 0.4f,
      head.y
  };

  DrawCircleV(eye, headRadius * 0.2f, BLACK);
}

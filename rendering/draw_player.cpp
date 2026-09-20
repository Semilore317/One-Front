#include "draw_player.hpp"
#include <algorithm>
#include <cmath>
#include <raylib.h>

void draw_player(const Player &player, float animationTime) {

  // 1. determine if the player is idle
  const bool isIdle = player.isGrounded && player.velocity.x == 0.0f;

  // 2.clacu;late the visual offset
  float idleOffset = 0.0f;
  if (isIdle) {
    constexpr float IDLE_SPEED = 3.0f;
    constexpr float IDLE_AMPLITUDE = 3.0f;
    idleOffset = std::sin(animationTime * IDLE_SPEED) * IDLE_AMPLITUDE;
  }

  // 3. setup base coordinates
  const float x = player.position.x;
  const float width = player.size.x;
  const float height = player.size.y;

  // apply the idle offset to upper body, but keep feet planted to the floor
  const float upperY = player.position.y + idleOffset;
  const float floorY = player.position.y + height;

  const float centerX = x + width * 0.5f;
  const float headRadius = std::min(width * 0.25f, height * 0.15f);

  // 4. Calculate joints using the offset Y
  const Vector2 head{centerX, upperY + headRadius};
  const Vector2 neck{centerX, upperY + headRadius * 2.0f};
  const Vector2 shoulders{centerX, upperY + height * 0.4f};
  const Vector2 hips{centerX, upperY + height * 0.65f};
  const Vector2 leftHand{x + width * 0.1f, upperY + height * 0.6f};
  const Vector2 rightHand{x + width * 0.9f, upperY + height * 0.6f};

  // foot stays anchored to the floor
  const Vector2 leftFoot{x + width * 0.1f, floorY};
  const Vector2 rightFoot{x + width * 0.9f, floorY};

  // 5.Draw the stick figure
  DrawCircleV(head, headRadius, WHITE);
  DrawLineV(neck, hips, WHITE);
  DrawLineV(hips, rightFoot, WHITE);
  DrawLineV(hips, leftFoot, WHITE);
  DrawLineV(shoulders, leftHand, WHITE);
  DrawLineV(shoulders, rightHand, WHITE);

  // draw the direction marker eye
  const float direction = player.facing == Facing::Right ? 1.0f : -1.0f;
  const Vector2 eye{head.x + direction * headRadius * 0.4f, head.y};
  DrawCircleV(eye, headRadius * 0.2f, BLACK);
}

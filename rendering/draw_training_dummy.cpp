#include "draw_training_dummy.hpp"
#include <algorithm>
#include <cmath>
#include <raylib.h>

void draw_training_dummy(const TrainingDummy &dummy, float animationTime) {
  // continuous idle animation (breathing/bobbing)
  constexpr float IDLE_SPEED = 2.5f;
  constexpr float IDLE_AMPLITUDE = 2.5f;
  const float idleOffset =
      std::sin(animationTime * IDLE_SPEED) * IDLE_AMPLITUDE;

  const float x = dummy.position.x;
  const float width = dummy.size.x;
  const float height = dummy.size.y;

  const float upperY = dummy.position.y + idleOffset;
  const float floorY = dummy.position.y + height;
  const float centerX = x + width * 0.5f;

  // Slightly different proportions: Larger head than the player
  const float headRadius = std::min(width * 0.3f, height * 0.18f);

  const Vector2 head{centerX, upperY + headRadius};
  const Vector2 neck{centerX, upperY + height * 2.0f};
  const Vector2 shoulders{centerX, upperY + height * 0.4f};
  const Vector2 hips{centerX, upperY + height * 0.65f};

  // Wider stance and arms to look more aggresive stance
  const Vector2 leftHand{x - width * 0.1f, upperY + height * 0.6f};
  const Vector2 rightHand{x + width * 1.1f, upperY + height * 0.6f};
  const Vector2 leftFoot{x, floorY};
  const Vector2 rightFoot{x + width, floorY};

  // Draw in RED to signify a target/enemy ,using thicker lines (2.0f);
  Color dummyColor = RED;

  DrawCircleV(head, headRadius, dummyColor);
  DrawLineEx(neck, hips, 2.0f, dummyColor);
  DrawLineEx(hips, rightFoot, 2.0f, dummyColor);
  DrawLineEx(hips, leftFoot, 2.0f, dummyColor);
  DrawLineEx(shoulders, leftHand, 2.0f, dummyColor);
  DrawLineEx(shoulders, rightHand, 2.0f, dummyColor);

  // Eye facing left (towards where the player usually approaches from )
  const Vector2 eye{head.x - headRadius * 0.4f, head.y};
  DrawCircleV(eye, headRadius * 0.2f, BLACK);
}

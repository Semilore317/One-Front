#include "draw_player.hpp"
#include <algorithm>
#include <cmath>
#include <raylib.h>

namespace {
constexpr float IDLE_SPEED{3.0f};
constexpr float IDLE_AMPLITUDE{2.0f};
} // namespace

void draw_player(const Player &player, float animationTime) {
	const bool isIdle = player.isGrounded && player.velocity.x == 0.0f;
	const float idleOffset =
	    isIdle ? std::sin(animationTime * IDLE_SPEED) * IDLE_AMPLITUDE : 0.0f;

	const float x = player.position.x;
	const float upperY = player.position.y + idleOffset;
	const float floorY = player.position.y + player.size.y;
	const float width = player.size.x;
	const float height = player.size.y;

	const float centerX = x + width * 0.5f;
	const float headRadius = std::min(width * 0.25f, height * 0.15f);

	const Vector2 head{centerX, upperY + headRadius};
	const Vector2 neck{centerX, upperY + headRadius * 2.0f};
	const Vector2 shoulders{centerX, upperY + height * 0.4f};
	const Vector2 hips{centerX, upperY + height * 0.65f};
	const Vector2 leftHand{x + width * 0.1f, upperY + height * 0.6f};
	const Vector2 rightHand{x + width * 0.9f, upperY + height * 0.6f};
	const Vector2 leftFoot{x + width * 0.1f, floorY};
	const Vector2 rightFoot{x + width * 0.9f, floorY};

	DrawCircleV(head, headRadius, WHITE);
	DrawLineV(neck, hips, WHITE);
	DrawLineV(hips, rightFoot, WHITE);
	DrawLineV(hips, leftFoot, WHITE);
	DrawLineV(shoulders, leftHand, WHITE);
	DrawLineV(shoulders, rightHand, WHITE);

	// Show the direction the player is facing.
	const float direction = player.facing == Facing::Right ? 1.0f : -1.0f;
	const Vector2 eye{head.x + direction * headRadius * 0.4f, head.y};
	DrawCircleV(eye, headRadius * 0.2f, BLACK);
}

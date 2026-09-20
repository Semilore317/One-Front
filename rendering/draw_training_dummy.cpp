#include "draw_training_dummy.hpp"

#include <cmath>
#include <raylib.h>

namespace {
constexpr float SWAY_SPEED{1.8f};
constexpr float SWAY_DISTANCE{2.0f};
constexpr float ARM_ROTATION{4.0f};
constexpr Color WOOD_LIGHT{181, 101, 29, 255};
constexpr Color WOOD_DARK{92, 51, 23, 255};

void draw_base(const TrainingDummy &dummy) {
	const Rectangle foot{
	    dummy.position.x,
	    dummy.position.y + dummy.size.y * 0.9f,
	    dummy.size.x,
	    dummy.size.y * 0.1f,
	};
	DrawRectangleRec(foot, WOOD_DARK);
}

void draw_post(const TrainingDummy &dummy) {
	const float postWidth = dummy.size.x * 0.16f;
	const Rectangle post{
	    dummy.position.x + (dummy.size.x - postWidth) * 0.5f,
	    dummy.position.y + dummy.size.y * 0.28f,
	    postWidth,
	    dummy.size.y * 0.64f,
	};
	DrawRectangleRec(post, WOOD_DARK);
}

void draw_arms(const TrainingDummy &dummy,
               float horizontalOffset,
               float rotation) {
	const float armWidth = dummy.size.x * 1.35f;
	const float armHeight = dummy.size.y * 0.09f;
	const Rectangle arms{
	    dummy.position.x + dummy.size.x * 0.5f + horizontalOffset,
	    dummy.position.y + dummy.size.y * 0.43f,
	    armWidth,
	    armHeight,
	};
	DrawRectanglePro(
	    arms, {armWidth * 0.5f, armHeight * 0.5f}, rotation, WOOD_LIGHT);
}

void draw_head(const TrainingDummy &dummy, float horizontalOffset) {
	const float radius = dummy.size.x * 0.32f;
	const Vector2 center{
	    dummy.position.x + dummy.size.x * 0.5f + horizontalOffset,
	    dummy.position.y + radius,
	};
	DrawCircleV(center, radius, WOOD_LIGHT);
	DrawCircleV({center.x - radius * 0.35f, center.y}, radius * 0.1f, BLACK);
}
} // namespace

void draw_training_dummy(const TrainingDummy &dummy, float animationTime) {
	const float cycle = std::sin(animationTime * SWAY_SPEED);
	const float horizontalOffset = cycle * SWAY_DISTANCE;
	const float armRotation = cycle * ARM_ROTATION;

	draw_base(dummy);
	draw_post(dummy);
	draw_arms(dummy, horizontalOffset, armRotation);
	draw_head(dummy, horizontalOffset);
}

#include "draw_training_dummy.hpp"

#include <cmath>
#include <raylib.h>

namespace {
constexpr float SWAY_SPEED{1.8f};
constexpr float SWAY_DISTANCE{1.5f};
constexpr float BREATH_DISTANCE{1.0f};
constexpr float LIMB_THICKNESS{3.0f};
constexpr Color DUMMY_BODY{210, 80, 70, 255};
constexpr Color DUMMY_ACCENT{250, 190, 70, 255};
constexpr Color DUMMY_SHADOW{105, 40, 45, 255};

void draw_humanoid(const TrainingDummy &dummy,
                   float horizontalOffset,
                   float verticalOffset) {
	const float x = dummy.position.x;
	const float y = dummy.position.y;
	const float width = dummy.size.x;
	const float height = dummy.size.y;
	const float centerX = x + width * 0.5f + horizontalOffset;
	const float floorY = y + height;
	const float headRadius = width * 0.28f;

	const Vector2 head{centerX, y + headRadius + verticalOffset};
	const Vector2 shoulders{centerX, y + height * 0.38f + verticalOffset};
	const Vector2 hips{centerX, y + height * 0.68f + verticalOffset};
	const Vector2 leftHand{x + width * 0.08f,
	                       y + height * 0.61f + verticalOffset};
	const Vector2 rightHand{x + width * 0.92f,
	                        y + height * 0.57f + verticalOffset};
	const Vector2 leftFoot{x + width * 0.18f, floorY};
	const Vector2 rightFoot{x + width * 0.82f, floorY};

	DrawLineEx(hips, leftFoot, LIMB_THICKNESS, DUMMY_SHADOW);
	DrawLineEx(hips, rightFoot, LIMB_THICKNESS, DUMMY_SHADOW);
	DrawLineEx(shoulders, hips, LIMB_THICKNESS + 1.0f, DUMMY_BODY);
	DrawLineEx(shoulders, leftHand, LIMB_THICKNESS, DUMMY_BODY);
	DrawLineEx(shoulders, rightHand, LIMB_THICKNESS, DUMMY_BODY);
	DrawCircleV(head, headRadius, DUMMY_BODY);

	const Rectangle visor{
	    head.x - headRadius * 0.65f,
	    head.y - headRadius * 0.2f,
	    headRadius * 1.3f,
	    headRadius * 0.35f,
	};
	DrawRectangleRec(visor, DUMMY_ACCENT);
	DrawCircleV(leftHand, LIMB_THICKNESS, DUMMY_ACCENT);
	DrawCircleV(rightHand, LIMB_THICKNESS, DUMMY_ACCENT);
}
} // namespace

void draw_training_dummy(const TrainingDummy &dummy, float animationTime) {
	const float cycle = std::sin(animationTime * SWAY_SPEED);
	const float horizontalOffset = cycle * SWAY_DISTANCE;
	const float verticalOffset =
	    std::cos(animationTime * SWAY_SPEED) * BREATH_DISTANCE;

	draw_humanoid(dummy, horizontalOffset, verticalOffset);
}

#include "draw_goal.hpp"

void draw_goal(Rectangle bounds) {
	constexpr float poleWidth{5.0f};
	constexpr float flagHeight{24.0f};

	DrawRectangleRec(bounds, Fade(GOLD, 0.2f));
	DrawRectangleLinesEx(bounds, 2.0f, GOLD);
	DrawRectangleRec({bounds.x, bounds.y, poleWidth, bounds.height}, RAYWHITE);
	DrawTriangle({bounds.x + poleWidth, bounds.y},
	             {bounds.x + bounds.width, bounds.y + flagHeight * 0.5f},
	             {bounds.x + poleWidth, bounds.y + flagHeight},
	             GOLD);
}

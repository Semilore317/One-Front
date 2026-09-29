#include "goal.hpp"

bool reaches_goal(Rectangle playerBounds, Rectangle goalBounds) {
	return playerBounds.x < goalBounds.x + goalBounds.width &&
	       playerBounds.x + playerBounds.width > goalBounds.x &&
	       playerBounds.y < goalBounds.y + goalBounds.height &&
	       playerBounds.y + playerBounds.height > goalBounds.y;
}

bool update_goal_completion(bool isComplete,
                            Rectangle playerBounds,
                            Rectangle goalBounds) {
	return isComplete || reaches_goal(playerBounds, goalBounds);
}

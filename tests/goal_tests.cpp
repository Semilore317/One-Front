#include "game/goal.hpp"

#include <iostream>

namespace {
bool expect(bool condition, const char *description) {
	if (condition)
		return true;

	std::cerr << description << '\n';
	return false;
}
} // namespace

int main() {
	constexpr Rectangle goal{100.0f, 100.0f, 40.0f, 60.0f};

	bool passed = true;
	passed &= expect(reaches_goal({90.0f, 120.0f, 30.0f, 50.0f}, goal),
	                 "player overlap should reach the goal");
	passed &= expect(reaches_goal({110.0f, 110.0f, 10.0f, 10.0f}, goal),
	                 "player inside the goal should reach it");
	passed &= expect(!reaches_goal({70.0f, 100.0f, 30.0f, 50.0f}, goal),
	                 "touching the left edge should not count as overlap");
	passed &= expect(!reaches_goal({140.0f, 100.0f, 30.0f, 50.0f}, goal),
	                 "touching the right edge should not count as overlap");
	passed &= expect(!reaches_goal({100.0f, 50.0f, 30.0f, 50.0f}, goal),
	                 "touching the top edge should not count as overlap");
	passed &= expect(!reaches_goal({100.0f, 160.0f, 30.0f, 50.0f}, goal),
	                 "touching the bottom edge should not count as overlap");
	passed &= expect(
	    update_goal_completion(false, {90.0f, 120.0f, 30.0f, 50.0f}, goal),
	    "overlap should set completion");
	passed &=
	    expect(update_goal_completion(true, {0.0f, 0.0f, 30.0f, 50.0f}, goal),
	           "completion should remain set after leaving the goal");
	passed &=
	    expect(!update_goal_completion(false, {0.0f, 0.0f, 30.0f, 50.0f}, goal),
	           "completion should remain clear before reaching the goal");

	return passed ? 0 : 1;
}

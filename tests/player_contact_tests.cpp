#include "game/controls.hpp"
#include "world/player/player.hpp"

#include <cmath>
#include <iostream>
#include <vector>

namespace {
constexpr float TEST_EPSILON{0.001f};

bool expect(bool condition, const char *description) {
	if (condition)
		return true;

	std::cerr << description << '\n';
	return false;
}

bool expect_near(float actual, float expected, const char *description) {
	return expect(std::abs(actual - expected) <= TEST_EPSILON, description);
}
} // namespace

int main() {
	constexpr float groundY{1000.0f};
	constexpr float leftBound{0.0f};
	constexpr float rightBound{1280.0f};

	Platform platform{{100.0f, 200.0f}, {180.0f, 15.0f}};
	std::vector<Platform> platforms{platform};
	Player player{{120.0f, 150.05f}, {30.0f, 50.0f}};

	player.update(
	    0.0f, Keyboard_Controls, groundY, leftBound, rightBound, platforms);

	bool passed = true;
	passed &= expect(player.isGrounded,
	                 "minor contact drift should preserve grounded state");

	platforms.front().position.x += 5.0f;
	platforms.front().movementDelta.x = 5.0f;
	player.update(
	    0.0f, Keyboard_Controls, groundY, leftBound, rightBound, platforms);
	passed &= expect_near(player.position.x,
	                      125.0f,
	                      "contact drift should not break platform carrying");

	Player unsupported{{120.0f, 150.2f}, {30.0f, 50.0f}};
	unsupported.update(
	    0.0f, Keyboard_Controls, groundY, leftBound, rightBound, platforms);
	passed &= expect(!unsupported.isGrounded,
	                 "contact outside tolerance should not count as support");

	return passed ? 0 : 1;
}

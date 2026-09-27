#include "game/camera/game_camera.hpp"
#include "world/player/player.hpp"
#include "world/world.hpp"

#include <cmath>
#include <iostream>

namespace {
constexpr float TEST_EPSILON{0.001f};

bool nearly_equal(float left, float right) {
	return std::abs(left - right) <= TEST_EPSILON;
}

bool expect_near(float actual, float expected, const char *description) {
	if (nearly_equal(actual, expected))
		return true;

	std::cerr << description << ": expected " << expected << ", got " << actual
	          << '\n';
	return false;
}
} // namespace

int main() {
	World viewportSizedWorld{0.0f, 1280.0f, -100.0f, 620.0f};
	Player player{{50.0f, 570.0f}, {30.0f, 50.0f}};
	GameCamera camera{1280.0f, 720.0f, player, viewportSizedWorld};

	bool passed = true;
	passed &= expect_near(camera.camera.target.x,
	                      640.0f,
	                      "narrow world is horizontally centered");
	passed &= expect_near(
	    camera.camera.target.y, 260.0f, "camera does not show below ground");

	passed &= expect_near(camera.camera.target.y,
	                      260.0f,
	                      "viewport-sized world is vertically centered");

	World tallWorld{0.0f, 1280.0f, -1380.0f, 620.0f};
	player.position = {50.0f, -1300.0f};
	GameCamera tallCamera{1280.0f, 720.0f, player, tallWorld};
	passed &= expect_near(tallCamera.camera.target.y,
	                      -1020.0f,
	                      "camera stops at the top world bound");

	player.position.y = 570.0f;
	tallCamera.update(10.0f, player, tallWorld);
	passed &= expect_near(tallCamera.camera.target.y,
	                      260.0f,
	                      "camera does not show below ground");

	World wideWorld{0.0f, 3000.0f, -100.0f, 620.0f};
	player.position = {1500.0f, 200.0f};
	GameCamera wideCamera{1280.0f, 720.0f, player, wideWorld};
	passed &= expect_near(wideCamera.camera.target.x,
	                      1515.0f,
	                      "wide world follows player center");

	player.position.x = -100.0f;
	GameCamera leftCamera{1280.0f, 720.0f, player, wideWorld};
	passed &= expect_near(leftCamera.camera.target.x,
	                      640.0f,
	                      "camera stops at the left world bound");

	player.position.x = 2990.0f;
	GameCamera rightCamera{1280.0f, 720.0f, player, wideWorld};
	passed &= expect_near(rightCamera.camera.target.x,
	                      2360.0f,
	                      "camera stops at the right world bound");

	return passed ? 0 : 1;
}

#include "world/levels/vertical_prototype.hpp"
#include "world/world.hpp"

#include <algorithm>
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
	constexpr float viewportHeight{720.0f};
	const LevelDefinition level = levels::vertical_prototype(1280.0f, 620.0f);
	World world{level};

	bool passed = true;
	passed &= expect(world.groundY - world.topBound >= viewportHeight * 2.5f,
	                 "prototype should span multiple screen heights");
	passed &= expect(world.platforms.size() >= 30,
	                 "prototype should contain a complete climbing route");
	passed &= expect(level.playerSpawn.x >= level.leftBound &&
	                     level.playerSpawn.x < level.rightBound &&
	                     level.playerSpawn.y >= level.topBound &&
	                     level.playerSpawn.y < level.groundY,
	                 "player spawn should be inside the playable bounds");
	passed &= expect(level.playerSpawn.y == level.groundY - 50.0f,
	                 "player spawn should start on the ground");

	const auto outsideBounds = std::ranges::find_if(
	    world.platforms, [&world](const Platform &platform) {
		    const float leftExtent =
		        platform.isMoving ? std::min(platform.startX, platform.endX)
		                          : platform.left();
		    const float rightExtent =
		        platform.isMoving
		            ? std::max(platform.startX, platform.endX) + platform.size.x
		            : platform.right();

		    return leftExtent < world.leftBound ||
		           rightExtent > world.rightBound ||
		           platform.top() < world.topBound ||
		           platform.bottom() > world.groundY;
	    });
	passed &= expect(outsideBounds == world.platforms.end(),
	                 "all platforms should remain inside the world bounds");

	const auto movingCount =
	    std::ranges::count_if(world.platforms, [](const Platform &platform) {
		    return platform.isMoving;
	    });
	passed &= expect(movingCount >= 8,
	                 "prototype should exercise moving-platform gameplay");

	const auto pusherCount =
	    std::ranges::count_if(world.platforms, [](const Platform &platform) {
		    return platform.isMoving && platform.size.x <= 30.0f &&
		           platform.size.y >= 60.0f;
	    });
	passed &= expect(pusherCount >= 2,
	                 "prototype should include narrow moving pushers");

	const bool hasCrouchClearance =
	    std::ranges::any_of(world.platforms, [&world](const Platform &floor) {
		    return std::ranges::any_of(
		        world.platforms, [&floor](const Platform &ceiling) {
			        const float clearance = floor.top() - ceiling.bottom();
			        const bool overlapsHorizontally =
			            floor.left() < ceiling.right() &&
			            floor.right() > ceiling.left();
			        return overlapsHorizontally && clearance >= 30.0f &&
			               clearance < 50.0f;
		        });
	    });
	passed &= expect(hasCrouchClearance,
	                 "prototype should include a crouch-height passage");

	const auto lowestPlatform = std::ranges::max_element(
	    world.platforms, {}, [](const Platform &platform) {
		    return platform.top();
	    });
	const auto highestPlatform = std::ranges::min_element(
	    world.platforms, {}, [](const Platform &platform) {
		    return platform.top();
	    });
	passed &= expect(lowestPlatform != world.platforms.end() &&
	                     highestPlatform != world.platforms.end() &&
	                     lowestPlatform->top() - highestPlatform->top() >=
	                         viewportHeight * 2.0f,
	                 "platform route should cover multiple screens");

	return passed ? 0 : 1;
}

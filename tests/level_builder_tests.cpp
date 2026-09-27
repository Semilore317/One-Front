#include "world/level/level_builder.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

namespace {
bool expect(bool condition, const char *description) {
	if (condition)
		return true;

	std::cerr << description << '\n';
	return false;
}

bool nearly_equal(float left, float right) {
	return std::abs(left - right) < 0.001f;
}

template <typename Function>
bool expect_invalid(Function function, const char *description) {
	try {
		function();
	} catch (const std::invalid_argument &) {
		return true;
	}

	std::cerr << description << '\n';
	return false;
}

levels::LevelBuilder test_level() {
	return levels::LevelBuilder{
	    levels::LevelBounds{.left = 0.0f,
	                        .right = 1280.0f,
	                        .groundY = 620.0f,
	                        .heightAboveGround = 2000.0f}};
}
} // namespace

int main() {
	using levels::above_ground;

	bool passed = true;
	auto builder = test_level();
	builder.spawn_on_ground(50.0f, 50.0f)
	    .platform(80.0f, above_ground(40.0f))
	    .moving_platform(300.0f,
	                     above_ground(100.0f),
	                     {.startX = 250.0f, .endX = 500.0f, .speed = 120.0f},
	                     160.0f)
	    .moving_wall(700.0f,
	                 above_ground(200.0f),
	                 {.startX = 650.0f, .endX = 800.0f, .speed = 100.0f});
	const LevelDefinition level = std::move(builder).build();

	passed &= expect(nearly_equal(level.topBound, -1380.0f),
	                 "builder should derive the top bound from world height");
	passed &=
	    expect(level.playerSpawn.x == 50.0f && level.playerSpawn.y == 570.0f,
	           "builder should place the player on the ground");
	passed &= expect(level.platforms.size() == 3,
	                 "builder should preserve authored platform order");
	passed &= expect(level.platforms[0].top() == 580.0f,
	                 "elevations should be measured above the ground");
	passed &= expect(level.platforms[1].isMoving &&
	                     level.platforms[1].startX == 250.0f &&
	                     level.platforms[1].endX == 500.0f,
	                 "moving platforms should retain their movement range");
	passed &= expect(level.platforms[2].size.x == 30.0f &&
	                     level.platforms[2].size.y == 70.0f,
	                 "moving walls should use wall-sized defaults");
	auto elevatedSpawn = test_level();
	elevatedSpawn.spawn(100.0f, above_ground(200.0f), 50.0f);
	const LevelDefinition elevatedLevel = std::move(elevatedSpawn).build();
	passed &= expect(elevatedLevel.playerSpawn.x == 100.0f &&
	                     elevatedLevel.playerSpawn.y == 370.0f,
	                 "builder should support elevated player spawns");

	passed &= expect_invalid(
	    [] {
		    auto missingSpawn = test_level();
		    [[maybe_unused]] const LevelDefinition missingLevel =
		        std::move(missingSpawn).build();
	    },
	    "builder should reject levels without a player spawn");
	passed &= expect_invalid(
	    [] {
		    auto duplicateSpawn = test_level();
		    duplicateSpawn.spawn_on_ground(50.0f, 50.0f);
		    duplicateSpawn.spawn_on_ground(100.0f, 50.0f);
	    },
	    "builder should reject duplicate player spawns");
	passed &= expect_invalid(
	    [] {
		    [[maybe_unused]] const auto invalidBounds =
		        levels::LevelBuilder{levels::LevelBounds{
		            .left = 0.0f,
		            .right = 1280.0f,
		            .groundY = std::numeric_limits<float>::infinity(),
		            .heightAboveGround = 2000.0f,
		        }};
	    },
	    "builder should reject non-finite level bounds");
	passed &= expect_invalid(
	    [] {
		    [[maybe_unused]] const auto invalidLeft =
		        levels::LevelBuilder{levels::LevelBounds{
		            .left = std::numeric_limits<float>::infinity(),
		            .right = 1280.0f,
		            .groundY = 620.0f,
		            .heightAboveGround = 2000.0f}};
	    },
	    "builder should reject a non-finite left bound");
	passed &= expect_invalid(
	    [] {
		    [[maybe_unused]] const auto invalidRight =
		        levels::LevelBuilder{levels::LevelBounds{
		            .left = 0.0f,
		            .right = std::numeric_limits<float>::infinity(),
		            .groundY = 620.0f,
		            .heightAboveGround = 2000.0f}};
	    },
	    "builder should reject a non-finite right bound");
	passed &= expect_invalid(
	    [] {
		    [[maybe_unused]] const auto invalidHeight =
		        levels::LevelBuilder{levels::LevelBounds{
		            .left = 0.0f,
		            .right = 1280.0f,
		            .groundY = 620.0f,
		            .heightAboveGround =
		                std::numeric_limits<float>::infinity()}};
	    },
	    "builder should reject a non-finite level height");
	passed &= expect_invalid(
	    [] {
		    [[maybe_unused]] const auto overflowingBounds =
		        levels::LevelBuilder{levels::LevelBounds{
		            .left = 0.0f,
		            .right = 1280.0f,
		            .groundY = std::numeric_limits<float>::lowest(),
		            .heightAboveGround = std::numeric_limits<float>::max(),
		        }};
	    },
	    "builder should reject an overflowing derived top bound");
	passed &= expect_invalid(
	    [] {
		    [[maybe_unused]] const auto reversedBounds = levels::LevelBuilder{
		        levels::LevelBounds{.left = 1280.0f,
		                            .right = 0.0f,
		                            .groundY = 620.0f,
		                            .heightAboveGround = 2000.0f}};
	    },
	    "builder should reject reversed horizontal bounds");
	passed &= expect_invalid(
	    [] {
		    auto reusedBuilder = test_level();
		    reusedBuilder.spawn_on_ground(50.0f, 50.0f);
		    [[maybe_unused]] const LevelDefinition first =
		        std::move(reusedBuilder).build();
		    [[maybe_unused]] const LevelDefinition second =
		        std::move(reusedBuilder).build();
	    },
	    "builder should reject a second build");
	passed &= expect_invalid(
	    [] {
		    auto outsideSpawn = test_level();
		    outsideSpawn.spawn_on_ground(1280.0f, 50.0f);
	    },
	    "builder should reject a spawn outside the horizontal bounds");
	passed &= expect_invalid(
	    [] {
		    auto outsideBounds = test_level();
		    outsideBounds.platform(1200.0f, above_ground(40.0f), 180.0f);
	    },
	    "builder should reject platforms outside the level bounds");
	passed &= expect_invalid(
	    [] {
		    auto zeroWidth = test_level();
		    zeroWidth.platform(300.0f, above_ground(40.0f), 0.0f);
	    },
	    "builder should reject zero-sized platforms");
	passed &= expect_invalid(
	    [] {
		    auto zeroHeight = test_level();
		    zeroHeight.platform(300.0f, above_ground(40.0f), 180.0f, 0.0f);
	    },
	    "builder should reject zero-height platforms");
	passed &= expect_invalid(
	    [] {
		    auto aboveBounds = test_level();
		    aboveBounds.platform(300.0f, above_ground(2010.0f));
	    },
	    "builder should reject platforms above the vertical bounds");
	passed &= expect_invalid(
	    [] {
		    auto belowGround = test_level();
		    belowGround.platform(300.0f, above_ground(0.0f));
	    },
	    "builder should reject platforms extending below ground");
	passed &= expect_invalid(
	    [] {
		    auto invalidMotion = test_level();
		    invalidMotion.moving_platform(
		        300.0f,
		        above_ground(100.0f),
		        {.startX = 500.0f, .endX = 250.0f, .speed = 120.0f});
	    },
	    "builder should reject reversed movement ranges");
	passed &= expect_invalid(
	    [] {
		    auto emptyMotion = test_level();
		    emptyMotion.moving_platform(
		        300.0f,
		        above_ground(100.0f),
		        {.startX = 300.0f, .endX = 300.0f, .speed = 120.0f});
	    },
	    "builder should reject movement ranges with no travel");
	passed &= expect_invalid(
	    [] {
		    auto outsideStart = test_level();
		    outsideStart.moving_platform(
		        200.0f,
		        above_ground(100.0f),
		        {.startX = 250.0f, .endX = 500.0f, .speed = 120.0f});
	    },
	    "builder should reject movers starting outside their range");
	passed &= expect_invalid(
	    [] {
		    auto beyondEnd = test_level();
		    beyondEnd.moving_platform(
		        600.0f,
		        above_ground(100.0f),
		        {.startX = 250.0f, .endX = 500.0f, .speed = 120.0f});
	    },
	    "builder should reject movers starting beyond their range");
	passed &= expect_invalid(
	    [] {
		    auto negativeElevation = test_level();
		    negativeElevation.platform(300.0f, above_ground(-10.0f));
	    },
	    "builder should reject negative platform elevations");
	passed &= expect_invalid(
	    [] {
		    auto invalidElevation = test_level();
		    invalidElevation.platform(
		        300.0f, above_ground(std::numeric_limits<float>::infinity()));
	    },
	    "builder should reject non-finite platform elevations");
	passed &= expect_invalid(
	    [] {
		    auto outsideMotion = test_level();
		    outsideMotion.moving_platform(
		        1000.0f,
		        above_ground(100.0f),
		        {.startX = 1000.0f, .endX = 1200.0f, .speed = 120.0f});
	    },
	    "builder should reject movement that leaves the level bounds");
	passed &= expect_invalid(
	    [] {
		    auto stoppedMotion = test_level();
		    stoppedMotion.moving_platform(
		        300.0f,
		        above_ground(100.0f),
		        {.startX = 250.0f, .endX = 500.0f, .speed = 0.0f});
	    },
	    "builder should reject nonpositive movement speeds");
	passed &= expect_invalid(
	    [] {
		    auto invalidSpeed = test_level();
		    invalidSpeed.moving_platform(
		        300.0f,
		        above_ground(100.0f),
		        {.startX = 250.0f,
		         .endX = 500.0f,
		         .speed = std::numeric_limits<float>::infinity()});
	    },
	    "builder should reject non-finite movement speeds");

	return passed ? 0 : 1;
}

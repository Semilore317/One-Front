#include "level_builder.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace {
void require(bool condition, const char *message) {
	if (!condition)
		throw std::invalid_argument{message};
}
} // namespace

levels::LevelBuilder::LevelBuilder(LevelBounds bounds):
    level_{bounds.left,
           bounds.right,
           bounds.groundY - bounds.heightAboveGround,
           bounds.groundY,
           {},
           {}} {
	require(std::isfinite(bounds.left) && std::isfinite(bounds.right) &&
	            std::isfinite(bounds.groundY) &&
	            std::isfinite(bounds.heightAboveGround),
	        "level bounds must be finite");
	require(std::isfinite(level_.topBound),
	        "derived level top bound must be finite");
	require(bounds.right > bounds.left,
	        "level right bound must be greater than its left bound");
	require(bounds.heightAboveGround > 0.0f, "level height must be positive");
}

levels::LevelBuilder &levels::LevelBuilder::spawn(float x,
                                                  Elevation feetElevation,
                                                  float playerHeight) & {
	require(!hasSpawn_, "level may define only one player spawn");
	require(playerHeight > 0.0f, "player height must be positive");
	require(x >= level_.leftBound && x < level_.rightBound,
	        "player spawn must be inside the horizontal level bounds");

	const float feetY = world_y(feetElevation);
	require(feetY - playerHeight >= level_.topBound,
	        "player spawn must fit inside the vertical level bounds");

	level_.playerSpawn = {x, feetY - playerHeight};
	hasSpawn_ = true;
	return *this;
}

levels::LevelBuilder &
levels::LevelBuilder::spawn_on_ground(float x, float playerHeight) & {
	return spawn(x, above_ground(0.0f), playerHeight);
}

levels::LevelBuilder &levels::LevelBuilder::platform(float x,
                                                     Elevation elevation,
                                                     float width,
                                                     float height) & {
	add_platform({{x, world_y(elevation)}, {width, height}});
	return *this;
}

levels::LevelBuilder &
levels::LevelBuilder::moving_platform(float x,
                                      Elevation elevation,
                                      HorizontalMotion motion,
                                      float width,
                                      float height) & {
	add_platform({{x, world_y(elevation)},
	              {width, height},
	              true,
	              motion.startX,
	              motion.endX,
	              motion.speed});
	return *this;
}

levels::LevelBuilder &levels::LevelBuilder::moving_wall(float x,
                                                        Elevation elevation,
                                                        HorizontalMotion motion,
                                                        float width,
                                                        float height) & {
	return moving_platform(x, elevation, motion, width, height);
}

LevelDefinition levels::LevelBuilder::build() && {
	require(!hasBuilt_, "level builder may only build once");
	require(hasSpawn_, "level must define a player spawn before build");
	hasBuilt_ = true;
	return std::move(level_);
}

float levels::LevelBuilder::world_y(Elevation elevation) const {
	require(std::isfinite(elevation.pixels) && elevation.pixels >= 0.0f,
	        "elevation must be finite and nonnegative");
	return level_.groundY - elevation.pixels;
}

void levels::LevelBuilder::add_platform(Platform platform) {
	require(platform.size.x > 0.0f && platform.size.y > 0.0f,
	        "platform dimensions must be positive");

	float leftExtent = platform.left();
	float rightExtent = platform.right();
	if (platform.isMoving) {
		require(platform.startX < platform.endX,
		        "moving platform range must run from left to right");
		require(std::isfinite(platform.speed) && platform.speed > 0.0f,
		        "moving platform speed must be finite and positive");
		require(platform.position.x >= platform.startX &&
		            platform.position.x <= platform.endX,
		        "moving platform must start inside its movement range");
		leftExtent = platform.startX;
		rightExtent = platform.endX + platform.size.x;
	}

	require(leftExtent >= level_.leftBound && rightExtent <= level_.rightBound,
	        "platform must remain inside the horizontal level bounds");
	require(platform.top() >= level_.topBound &&
	            platform.bottom() <= level_.groundY,
	        "platform must remain inside the vertical level bounds");

	level_.platforms.push_back(platform);
}

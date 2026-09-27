#pragma once

#include "level_definition.hpp"

namespace levels {
struct Elevation {
	float pixels;
};

[[nodiscard]] constexpr Elevation above_ground(float pixels) {
	return {pixels};
}

struct HorizontalMotion {
	// Range values describe the moving platform's left edge.
	float startX;
	float endX;
	float speed;
};

struct LevelBounds {
	float left;
	float right;
	float groundY;
	float heightAboveGround;
};

class LevelBuilder {
  public:
	explicit LevelBuilder(LevelBounds bounds);

	LevelBuilder &spawn(float x, Elevation feetElevation, float playerHeight) &;
	LevelBuilder &spawn_on_ground(float x, float playerHeight) &;
	LevelBuilder &platform(float x,
	                       Elevation elevation,
	                       float width = 180.0f,
	                       float height = 15.0f) &;
	LevelBuilder &moving_platform(float x,
	                              Elevation elevation,
	                              HorizontalMotion motion,
	                              float width = 180.0f,
	                              float height = 15.0f) &;
	LevelBuilder &moving_wall(float x,
	                          Elevation elevation,
	                          HorizontalMotion motion,
	                          float width = 30.0f,
	                          float height = 70.0f) &;

	[[nodiscard]] LevelDefinition build() &&;

  private:
	LevelDefinition level_;
	bool hasSpawn_{false};
	bool hasBuilt_{false};

	[[nodiscard]] float world_y(Elevation elevation) const;
	void add_platform(Platform platform);
};
} // namespace levels

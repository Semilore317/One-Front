#include "vertical_prototype.hpp"
#include "../level/level_builder.hpp"

#include <utility>

namespace {
constexpr float PROTOTYPE_WORLD_HEIGHT{2000.0f};
constexpr float PLAYER_HEIGHT{50.0f};
constexpr float PLAYER_SPAWN_X{50.0f};
constexpr float TIMING_PLATFORM_WIDTH{160.0f};
constexpr float PRECISION_LEDGE_WIDTH{150.0f};
constexpr float RECOVERY_LEDGE_WIDTH{170.0f};
constexpr float TIMED_JUMP_WIDTH{180.0f};
} // namespace

LevelDefinition levels::vertical_prototype(float rightBound, float groundY) {
	LevelBuilder level{
	    LevelBounds{.left = 0.0f,
	                .right = rightBound,
	                .groundY = groundY,
	                .heightAboveGround = PROTOTYPE_WORLD_HEIGHT}};
	level.spawn_on_ground(PLAYER_SPAWN_X, PLAYER_HEIGHT);

	// Opening climb: wide, forgiving jumps introduce the route.
	level.platform(80.0f, above_ground(40.0f));
	level.platform(340.0f, above_ground(95.0f));
	level.platform(650.0f, above_ground(150.0f));
	level.platform(960.0f, above_ground(205.0f));
	level.moving_platform(720.0f,
	                      above_ground(260.0f),
	                      {.startX = 620.0f, .endX = 850.0f, .speed = 140.0f});
	level.platform(470.0f, above_ground(315.0f));
	level.platform(180.0f, above_ground(370.0f));
	level.moving_platform(400.0f,
	                      above_ground(425.0f),
	                      {.startX = 350.0f, .endX = 700.0f, .speed = 180.0f});
	level.platform(760.0f, above_ground(480.0f));
	level.platform(1040.0f, above_ground(535.0f));

	// Timing bridge: alternating movers make the player wait or commit.
	level.platform(820.0f, above_ground(590.0f));
	level.moving_platform(540.0f,
	                      above_ground(645.0f),
	                      {.startX = 420.0f, .endX = 700.0f, .speed = 140.0f},
	                      TIMING_PLATFORM_WIDTH);
	level.moving_platform(240.0f,
	                      above_ground(700.0f),
	                      {.startX = 160.0f, .endX = 430.0f, .speed = 160.0f},
	                      TIMING_PLATFORM_WIDTH);

	// A 40 px tunnel forces the standing-height clearance check to keep the
	// player crouched until they leave the overhang.
	level.platform(70.0f, above_ground(755.0f), 250.0f);
	level.platform(70.0f, above_ground(810.0f), 250.0f);
	level.moving_platform(300.0f,
	                      above_ground(810.0f),
	                      {.startX = 250.0f, .endX = 600.0f, .speed = 180.0f},
	                      PRECISION_LEDGE_WIDTH);
	level.platform(650.0f, above_ground(865.0f));

	// Pusher gauntlet: moving walls sweep across otherwise safe ledges.
	level.platform(870.0f, above_ground(920.0f), 260.0f);
	level.moving_wall(920.0f,
	                  above_ground(990.0f),
	                  {.startX = 850.0f, .endX = 1060.0f, .speed = 140.0f});
	level.platform(680.0f, above_ground(975.0f), 170.0f);
	level.platform(430.0f, above_ground(1030.0f), 190.0f);
	level.moving_wall(520.0f,
	                  above_ground(1100.0f),
	                  {.startX = 390.0f, .endX = 610.0f, .speed = 150.0f});
	level.platform(160.0f, above_ground(1085.0f), 190.0f);

	// Final ascent: shorter ledges combine precision jumps and movers.
	level.platform(60.0f, above_ground(1140.0f), PRECISION_LEDGE_WIDTH);
	level.moving_platform(240.0f,
	                      above_ground(1195.0f),
	                      {.startX = 200.0f, .endX = 520.0f, .speed = 180.0f},
	                      PRECISION_LEDGE_WIDTH);
	level.platform(570.0f, above_ground(1250.0f), PRECISION_LEDGE_WIDTH);
	level.platform(780.0f, above_ground(1305.0f), RECOVERY_LEDGE_WIDTH);
	level.moving_platform(980.0f,
	                      above_ground(1360.0f),
	                      {.startX = 960.0f, .endX = 1000.0f, .speed = 80.0f},
	                      TIMED_JUMP_WIDTH);
	level.platform(760.0f, above_ground(1415.0f), RECOVERY_LEDGE_WIDTH);
	level.platform(540.0f, above_ground(1470.0f), PRECISION_LEDGE_WIDTH);
	level.platform(320.0f, above_ground(1525.0f), PRECISION_LEDGE_WIDTH);
	level.moving_platform(80.0f,
	                      above_ground(1580.0f),
	                      {.startX = 60.0f, .endX = 300.0f, .speed = 170.0f},
	                      PRECISION_LEDGE_WIDTH);
	level.platform(390.0f, above_ground(1635.0f), PRECISION_LEDGE_WIDTH);
	level.platform(610.0f, above_ground(1690.0f), PRECISION_LEDGE_WIDTH);
	level.platform(830.0f, above_ground(1745.0f), PRECISION_LEDGE_WIDTH);
	level.platform(1030.0f, above_ground(1800.0f), 170.0f);

	return std::move(level).build();
}

#include "vertical_prototype.hpp"

namespace {
constexpr float PLATFORM_HEIGHT{15.0f};
constexpr float PLATFORM_WIDTH{180.0f};
constexpr float PROTOTYPE_WORLD_HEIGHT{2000.0f};
constexpr float PLAYER_HEIGHT{50.0f};
constexpr float PLAYER_SPAWN_X{50.0f};
constexpr float TIMING_PLATFORM_WIDTH{160.0f};
constexpr float PRECISION_LEDGE_WIDTH{150.0f};
constexpr float RECOVERY_LEDGE_WIDTH{170.0f};
constexpr float TIMED_JUMP_WIDTH{180.0f};

Platform ledge(float x, float y, float width = PLATFORM_WIDTH) {
	return {{x, y}, {width, PLATFORM_HEIGHT}};
}

Platform horizontal_mover(float x,
                          float y,
                          float startX,
                          float endX,
                          float speed,
                          float width = PLATFORM_WIDTH) {
	return {{x, y}, {width, PLATFORM_HEIGHT}, true, startX, endX, speed};
}

Platform wall_pusher(float x,
                     float y,
                     float startX,
                     float endX,
                     float speed,
                     float height = 70.0f) {
	return {{x, y}, {30.0f, height}, true, startX, endX, speed};
}
} // namespace

LevelDefinition levels::vertical_prototype(float rightBound, float groundY) {
	const auto y = [groundY](float heightAboveGround) {
		return groundY - heightAboveGround;
	};

	return {
	    0.0f,
	    rightBound,
	    groundY - PROTOTYPE_WORLD_HEIGHT,
	    groundY,
	    {PLAYER_SPAWN_X, groundY - PLAYER_HEIGHT},
	    {
	        // Opening climb: wide, forgiving jumps introduce the route.
	        ledge(80.0f, y(40.0f)),
	        ledge(340.0f, y(95.0f)),
	        ledge(650.0f, y(150.0f)),
	        ledge(960.0f, y(205.0f)),
	        horizontal_mover(720.0f, y(260.0f), 620.0f, 850.0f, 140.0f),
	        ledge(470.0f, y(315.0f)),
	        ledge(180.0f, y(370.0f)),
	        horizontal_mover(400.0f, y(425.0f), 350.0f, 700.0f, 180.0f),
	        ledge(760.0f, y(480.0f)),
	        ledge(1040.0f, y(535.0f)),

	        // Timing bridge: alternating movers make the player wait or commit.
	        ledge(820.0f, y(590.0f)),
	        horizontal_mover(540.0f,
	                         y(645.0f),
	                         420.0f,
	                         700.0f,
	                         140.0f,
	                         TIMING_PLATFORM_WIDTH),
	        horizontal_mover(240.0f,
	                         y(700.0f),
	                         160.0f,
	                         430.0f,
	                         160.0f,
	                         TIMING_PLATFORM_WIDTH),
	        // A 40 px tunnel forces the standing-height clearance check to
	        // keep the player crouched until they leave the overhang.
	        ledge(70.0f, y(755.0f), 250.0f),
	        ledge(70.0f, y(810.0f), 250.0f),
	        horizontal_mover(300.0f,
	                         y(810.0f),
	                         250.0f,
	                         600.0f,
	                         180.0f,
	                         PRECISION_LEDGE_WIDTH),
	        ledge(650.0f, y(865.0f)),

	        // Pusher gauntlet: moving walls sweep across otherwise safe ledges.
	        ledge(870.0f, y(920.0f), 260.0f),
	        wall_pusher(920.0f, y(990.0f), 850.0f, 1060.0f, 140.0f),
	        ledge(680.0f, y(975.0f), 170.0f),
	        ledge(430.0f, y(1030.0f), 190.0f),
	        wall_pusher(520.0f, y(1100.0f), 390.0f, 610.0f, 150.0f),
	        ledge(160.0f, y(1085.0f), 190.0f),

	        // Final ascent: shorter ledges combine precision jumps and movers.
	        ledge(60.0f, y(1140.0f), PRECISION_LEDGE_WIDTH),
	        horizontal_mover(240.0f,
	                         y(1195.0f),
	                         200.0f,
	                         520.0f,
	                         180.0f,
	                         PRECISION_LEDGE_WIDTH),
	        ledge(570.0f, y(1250.0f), PRECISION_LEDGE_WIDTH),
	        ledge(780.0f, y(1305.0f), RECOVERY_LEDGE_WIDTH),
	        horizontal_mover(
	            980.0f, y(1360.0f), 960.0f, 1000.0f, 80.0f, TIMED_JUMP_WIDTH),
	        ledge(760.0f, y(1415.0f), RECOVERY_LEDGE_WIDTH),
	        ledge(540.0f, y(1470.0f), PRECISION_LEDGE_WIDTH),
	        ledge(320.0f, y(1525.0f), PRECISION_LEDGE_WIDTH),
	        horizontal_mover(80.0f,
	                         y(1580.0f),
	                         60.0f,
	                         300.0f,
	                         170.0f,
	                         PRECISION_LEDGE_WIDTH),
	        ledge(390.0f, y(1635.0f), PRECISION_LEDGE_WIDTH),
	        ledge(610.0f, y(1690.0f), PRECISION_LEDGE_WIDTH),
	        ledge(830.0f, y(1745.0f), PRECISION_LEDGE_WIDTH),
	        ledge(1030.0f, y(1800.0f), 170.0f),
	    },
	};
}

#include "./game.hpp"
#include "../rendering/draw_player.hpp"
#include "raylib.h"

constexpr float PLAYER_HEIGHT = 50.0f;
constexpr float PLAYER_WIDTH = 30.0f;
constexpr float PLAYER_SPAWN_X = 50.0f;
constexpr float GROUND_OFFSET = 100.0f;

Game::Game():
    world{
        WINDOW_WIDTH,
        WINDOW_HEIGHT - GROUND_OFFSET,
    },
    player{{PLAYER_SPAWN_X, world.groundY - PLAYER_HEIGHT},
           {PLAYER_WIDTH, PLAYER_HEIGHT}},
    controls{WASD_Controls} {}

void Game::update(float deltaTime) {
	// update things belonging to the game
	player.update(deltaTime,
	              controls,
	              world.groundY,
	              world.leftBound,
	              world.rightBound,
	              world.platforms);
}

void Game::draw() const {
	// draw things belonging to the game

	// the ground
	DrawLine(
	    world.leftBound, world.groundY, world.rightBound, world.groundY, BROWN);

	// draw the platforms
	for (const Platform &platform : world.platforms)
		DrawRectangleV(platform.position, platform.size, BROWN);

	/*
	// TEMP: basic visualization until player renderer is merged
	DrawRectangleV(player.position, player.size, RED);

	float markerX = player.facing == Facing::Right
	    ? player.position.x + player.size.x - 5
	    : player.position.x;

	DrawRectangle(markerX, player.position.y + 10, 5, 10, WHITE);
	*/
	// 1. define health bar dimensions and screen positions within game
	float barX = 20.0f;
	float barY = 20.0f;
	float maxBarWidth = 200.0f;
	float barHeight = 20.0f;

	// 2.calculate the health ratio between (o.o and 1.0).
	float healthRatio = player.current_health / player.max_health;

	// 3. draw the background (Empty/missing health)
	DrawRectangle(barX, barY, maxBarWidth, barHeight, DARKGRAY);

	// 4.draw the foreround (currenthealth) scaled by the ratio.
	DrawRectangle(barX, barY, maxBarWidth * healthRatio, barHeight, GREEN);

	draw_player(player);
}

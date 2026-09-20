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
	// the ground
	DrawLine(
	    world.leftBound, world.groundY, world.rightBound, world.groundY, BROWN);

	// draw the platforms
	for (const Platform &platform : world.platforms)
		DrawRectangleV(platform.position, platform.size, BROWN);

	// health bar dimensions and size
	float barX = 20.0f;
	float barY = 20.0f;
	float maxBarWidth = 200.0f;
	float barHeight = 20.0f;

	float healthRatio = player.currentHealth / player.maxHealth;

	// background and foreground for healthbar
	DrawRectangle(barX, barY, maxBarWidth, barHeight, DARKGRAY);
	DrawRectangle(barX, barY, maxBarWidth * healthRatio, barHeight, GREEN);

	draw_player(player);
}

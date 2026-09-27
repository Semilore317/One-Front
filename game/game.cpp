#include "./game.hpp"
#include "../rendering/draw_player.hpp"
#include "raylib.h"
#include <algorithm>

constexpr float PLAYER_HEIGHT = 50.0f;
constexpr float PLAYER_WIDTH = 30.0f;
constexpr float PLAYER_SPAWN_X = 50.0f;
constexpr float GROUND_OFFSET = 100.0f;

Game::Game():
    world{
        World::vertical_prototype(WINDOW_WIDTH, WINDOW_HEIGHT - GROUND_OFFSET)},
    player{{PLAYER_SPAWN_X, world.groundY - PLAYER_HEIGHT},
           {PLAYER_WIDTH, PLAYER_HEIGHT}},
    camera{WINDOW_WIDTH, WINDOW_HEIGHT, player, world},
    controls{WASD_Controls} {}

void Game::update(float deltaTime) {
	// update things belonging to the game
	world.update(deltaTime);
	player.update(deltaTime,
	              controls,
	              world.groundY,
	              world.leftBound,
	              world.rightBound,
	              world.platforms);
	camera.update(deltaTime, player, world);
}

void Game::draw() const {
	BeginMode2D(camera.camera);
	draw_world();
	EndMode2D();

	draw_hud();
}

void Game::draw_world() const {
	// the ground
	DrawLine(
	    world.leftBound, world.groundY, world.rightBound, world.groundY, BROWN);

	// draw the platforms
	for (const Platform &platform : world.platforms)
		DrawRectangleV(platform.position, platform.size, BROWN);

	draw_player(player);

	/* Temporary Visualization of attack hitbox */
	// TODO: remove later on with proper attack animations
	if (player.isAttacking) {
		DrawRectangleRec(player.attack_hitbox(), Fade(RED, 0.45f));
	}
}

void Game::draw_hud() const {
	// health bar dimensions and size
	constexpr float barX = 20.0f;
	constexpr float barY = 20.0f;
	constexpr float maxBarWidth = 200.0f;
	constexpr float barHeight = 20.0f;

	const float healthRatio =
	    std::clamp(player.currentHealth / player.maxHealth, 0.0f, 1.0f);

	// background and foreground for healthbar
	DrawRectangle(barX, barY, maxBarWidth, barHeight, DARKGRAY);
	DrawRectangle(barX, barY, maxBarWidth * healthRatio, barHeight, GREEN);
}

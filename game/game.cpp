#include "./game.hpp"
#include "../rendering/draw_goal.hpp"
#include "../rendering/draw_player.hpp"
#include "../world/levels/vertical_prototype.hpp"
#include "./goal.hpp"
#include "raylib.h"
#include <algorithm>

constexpr float PLAYER_HEIGHT = 50.0f;
constexpr float PLAYER_WIDTH = 30.0f;
constexpr float GROUND_OFFSET = 100.0f;

Game::Game():
    Game{levels::vertical_prototype(WINDOW_WIDTH,
                                    WINDOW_HEIGHT - GROUND_OFFSET)} {}

Game::Game(const LevelDefinition &level):
    world{level},
    player{level.playerSpawn, {PLAYER_WIDTH, PLAYER_HEIGHT}},
    camera{WINDOW_WIDTH, WINDOW_HEIGHT, player, world},
    controls{WASD_Controls},
    levelComplete{false} {}

void Game::update(float deltaTime) {
	// update things belonging to the game
	world.update(deltaTime);
	player.update(deltaTime,
	              controls,
	              world.groundY,
	              world.leftBound,
	              world.rightBound,
	              world.platforms);
	levelComplete = update_goal_completion(
	    levelComplete,
	    {player.position.x, player.position.y, player.size.x, player.size.y},
	    world.goal);
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

	draw_goal(world.goal);

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

	if (levelComplete) {
		constexpr const char *message{"SUMMIT REACHED"};
		constexpr int fontSize{40};
		const int textWidth = MeasureText(message, fontSize);
		DrawText(message, (WINDOW_WIDTH - textWidth) / 2, 40, fontSize, GOLD);
	}
}

#pragma once

#include "./../world/level/level_definition.hpp"
#include "./../world/player/player.hpp"
#include "./../world/world.hpp"
#include "./camera/game_camera.hpp"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

struct Game {
	Game();

	World world;
	Player player;
	GameCamera camera;
	Controls controls;

	void update(float deltaTime);
	void draw() const;

  private:
	explicit Game(const LevelDefinition &level);
	void draw_world() const;
	void draw_hud() const;
};

#include "game/game.hpp"
#include "raylib.h"

int main() {
	InitWindow(1280, 720, "One Front");

	Game game;

	while (!WindowShouldClose()) {
		const float deltaTime = GetFrameTime();

		game.update(deltaTime);

		BeginDrawing();
		ClearBackground(Color(0, 0, 0, 255));

		game.draw();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

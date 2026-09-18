#include "game/game.hpp"
#include <raylib.h>

int main() {
  Game game = create_game();

  while (!WindowShouldClose()) {
    const float deltaTime = GetFrameTime();

    update_game(game, deltaTime);

    BeginDrawing();
    ClearBackground(Color(0, 0, 0, 255));

    draw_game(game);
    EndDrawing();
  }
}

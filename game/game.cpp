#include "game.hpp"
#include "../rendering/draw_player.hpp"

Game create_game() {
  Game game;
  // temporary placeholder that starts the player at coordinates (400,300).
  game.player.position.x = 400.0f;
  game.player.position.y = 300.0f;
  return game;
}

Game update_game(Game &game, float deltaTime) {
  // Nothing needs to happen here return
  return game;
}

Game draw_game(const Game &game) {
  // here is wee we hooked in our player rendering logic
  draw_player(game.player);
  return game;
}

#include "./game.hpp"

Game::Game(): 
    player{
        {50, WINDOW_HEIGHT - 100}, 
        {30,50}
    },
    controls{WASD_Controls}{}

void Game::update(float deltaTime) {
    // update things belonging to the game
    player.update(deltaTime, controls, WINDOW_HEIGHT - 100, 0, WINDOW_WIDTH);
}

void Game::draw() const{
    // draw things belonging to the game
    // TEMP: basic visualization until player renderer is merged
    DrawRectangleV(player.position, player.size, RED);
}
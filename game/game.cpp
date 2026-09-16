#include "./game.hpp"

Game::Game(): 
    player{
        {50, WINDOW_HEIGHT - 100}, 
        {30,50}
    },
    controls{WASD_Controls}{}

void Game::update(float deltaTime) {
    // update things belonging to the game
    player.update(deltaTime, controls);
}

void Game::draw() {
    // draw things belonging to the game
    player.draw();
}
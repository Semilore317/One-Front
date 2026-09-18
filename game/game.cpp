#include "./game.hpp"
#include "raylib.h"

constexpr float PLAYER_HEIGHT = 50;
constexpr float PLAYER_WIDTH = 30;
constexpr float PLAYER_SPAWN_X = 50;

Game::Game() : world{
                   0,
                   WINDOW_WIDTH,
                   WINDOW_HEIGHT - 100,
               },
               player{
                   {PLAYER_SPAWN_X, world.groundY - PLAYER_HEIGHT},
                   {PLAYER_WIDTH, PLAYER_HEIGHT}
               },
               controls{WASD_Controls} {
}

void Game::update(float deltaTime) {
    // update things belonging to the game
    player.update(
        deltaTime,
        controls,
        world.groundY,
        world.leftBound,
        world.rightBound,
        world.platforms
    );
}

void Game::draw() const {
    // draw things belonging to the game
     
    // the ground
    DrawLine(
        world.leftBound, 
        world.groundY, 
        world.rightBound, 
        world.groundY, 
        BROWN);

     // draw the platforms
     for(const Platform& platform: world.platforms)
        DrawRectangleV(platform.position, platform.size, BROWN);
     
    // TEMP: basic visualization until player renderer is merged
    DrawRectangleV(player.position, player.size, RED);
}

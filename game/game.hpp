#include "./../world/player/player.hpp"

struct Game{
    Player player;
};

Game create_game();
Game update_game(Game& game, float deltaTime);
Game draw_game(const Game& game);
#include "./../world/player/player.hpp"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

struct Game{
    Game();

    Player player;
    Controls controls;
    
    void update(float deltaTime);
    void draw();
};

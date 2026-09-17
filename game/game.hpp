#include "./../world/player/player.hpp"
#include "./../world/world.hpp"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

struct Game{
    Game();

    World world;
    Player player;
    Controls controls;
    
    void update(float deltaTime);
    void draw() const;
};

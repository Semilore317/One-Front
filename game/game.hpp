#include "../world/training_dummy/training_dummy.hpp"
#include "./../world/player/player.hpp"
#include "./../world/world.hpp"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

struct Game {
  Game();

  World world;
  Player player;
  Controls controls;

  void update(float deltaTime);
  void draw() const;

  // inside your Game or World class/struct:
  TrainingDummy dummy{{600.0f, 400.0f},
                      {50.0f, 100.0f}}; // Adjust X/Y coordinates as needed
};

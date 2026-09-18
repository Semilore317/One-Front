#include "./world.hpp"

World::World(float leftBound, float rightBound, float groundY)
    : leftBound(leftBound), rightBound(rightBound), groundY(groundY),
      platforms({
          {{120, 580}, {180, 15}},
          {{360, 550}, {180, 15}},
          {{650, 500}, {180, 15}},
          {{920, 500}, {160, 15}},
      }) {}

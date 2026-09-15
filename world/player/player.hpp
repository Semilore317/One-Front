#pragma once

#include "raylib.h"
#include "./../../game/controls.hpp"

struct Player{
    Player();
    Player(Vector2 position, Vector2 size);

    Vector2 position;
    Vector2 velocity;
    Vector2 size;

    void update(float deltaTime, const Controls& controls);
    void draw() const;
};
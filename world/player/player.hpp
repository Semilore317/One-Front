#pragma once

#include "raylib.h"
#include "./../../game/controls.hpp"

struct Player{
    Player();
    Player(Vector2 position, Vector2 size);

    bool isGrounded;
    Vector2 position;
    Vector2 velocity;
    Vector2 size;

    void apply_gravity(float deltaTime);
    void update(float deltaTime, const Controls& controls, float groundY);
    void draw() const;
};
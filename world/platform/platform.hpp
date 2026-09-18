#pragma once

#include <raylib.h>

struct Platform {
    Vector2 position;
    Vector2 size;

    float left() const{return position.x;}
    float right() const{return position.x + size.x;}
    float top() const{return position.y;}
    float bottom() const{return position.y + size.y;}
};

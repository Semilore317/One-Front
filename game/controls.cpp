#include "./controls.hpp"
#include "raylib.h"

bool KeyBinding::is_down() const {
	return IsKeyDown(primary) || IsKeyDown(alternate);
}

bool KeyBinding::is_pressed() const {
	return IsKeyPressed(primary) || IsKeyPressed(alternate);
}

const Controls Keyboard_Controls{
    {KEY_A, KEY_LEFT},
    {KEY_D, KEY_RIGHT},
    {KEY_W, KEY_UP},
    {KEY_S, KEY_DOWN},

    {KEY_J, KEY_Z},
    {KEY_K, KEY_X},
    {KEY_L, KEY_C},
};

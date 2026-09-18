#pragma once

// i need to include the player header so the file knows what "Player" is.
// goin up one directory (..) then into world/player/.

#include "../world/player/player.hpp"

// the function requested by my partner in the issue
void draw_player(const Player &player);

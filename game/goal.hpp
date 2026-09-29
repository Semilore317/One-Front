#pragma once

#include "raylib.h"

[[nodiscard]] bool reaches_goal(Rectangle playerBounds, Rectangle goalBounds);
[[nodiscard]] bool update_goal_completion(bool isComplete,
                                          Rectangle playerBounds,
                                          Rectangle goalBounds);

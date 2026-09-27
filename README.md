# One Front

One Front is an early 2D platforming prototype built with C++20 and raylib.
It focuses on responsive movement, solid platform interactions, directional
combat, and a multi-screen vertical route.

<img width="1344" height="756" alt="Recording 2026-09-20 224429" src="https://github.com/user-attachments/assets/a727cef4-53e2-4796-938b-5f0f73fb7352" />

## Current features

- Horizontal movement, jumping, gravity, crouching, and airborne fast-fall
- Static and horizontal moving platforms
- Platform landing, side, underside, carrying, and pushing collisions
- Left, right, upward, and downward attacks with cooldowns
- Downward pogo recoil from platforms
- Screen-space health HUD
- Smooth bounded camera following
- Multi-screen vertical prototype level with movers, pushers, and timing
  sections

## Controls

| Action | WASD controls | Arrow controls |
| --- | --- | --- |
| Move | `A` / `D` | Left / Right |
| Jump | `W` | Up |
| Crouch or fast-fall | `S` | Down |
| Primary attack | `J` | `Z` |
| Up attack | `W` + `J` | Up + `Z` |
| Down attack | `S` + `J` while airborne | Down + `Z` while airborne |

`K` / `L` and `X` / `C` are reserved for additional attacks.

## Requirements

- Git
- CMake
- A C++20 compiler

raylib 5.5 is downloaded automatically when CMake configures the project.

## Build

Clone and configure the repository:

```sh
git clone https://github.com/Semilore317/One-Front.git
cd One-Front
cmake -S . -B build
```

Build the game:

```sh
cmake --build build
```

Multi-config generators such as Visual Studio can select a configuration:

```sh
cmake --build build --config Release --target OneFront
```

Run the generated `OneFront` executable from the build directory.

## Level authoring

Levels are C++ functions that return a `LevelDefinition`. Use `LevelBuilder` to
describe bounds, the player spawn, static platforms, moving platforms, and
moving walls without changing world simulation code:

```cpp
#include "world/level/level_builder.hpp"

#include <utility>

LevelDefinition example_level(float rightBound, float groundY) {
    levels::LevelBuilder level{levels::LevelBounds{
        .left = 0.0f,
        .right = rightBound,
        .groundY = groundY,
        .heightAboveGround = 1200.0f}};
    level.spawn_on_ground(50.0f, 50.0f);
    level.platform(80.0f, levels::above_ground(40.0f));
    level.moving_platform(
        300.0f,
        levels::above_ground(100.0f),
        {.startX = 250.0f, .endX = 500.0f, .speed = 120.0f});

    return std::move(level).build();
}
```

`above_ground()` measures the platform's top edge upward from the level's
ground line, so layouts remain readable when the window or ground position
changes. The builder rejects missing spawns, invalid dimensions or movement
ranges, and platforms that leave the declared level bounds. Use `spawn()` with
an `above_ground()` elevation when a level should start the player somewhere
other than the ground.

## Status

One Front is actively developed and remains a gameplay prototype. The current
level is intended to demonstrate its mechanics, not represent finished content.

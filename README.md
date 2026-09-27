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

## Status

One Front is actively developed and remains a gameplay prototype. The current
level is intended to demonstrate its mechanics, not represent finished content.

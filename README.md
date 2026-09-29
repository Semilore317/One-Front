# One Front

This is a 2D platforming game built with C++20 and Raylib.
It's still quite early in development and  has the most basic  features in place

<img width="1344" height="756" alt="One Front" src="assets\Recording 2026-09-29 181344.gif" />

# How to Play
Your goal is to climb to the top of the level and reach the flag. Use the platforms
and your goal is to make your way upward.

## Controls

| Action | Control |
| --- | --- |
| Move left or right | `A` / `D` |
| Jump | `W` |
| Crouch | Hold `S` while grounded |
| Fast-fall | Press `S` while airborne |
| Attack | `J` |
| Attack upward | Hold `W`, then press `J` |
| Attack downward | While airborne, hold `S`, then press `J` |


these are the defaults for now... but the code is structured such that there's room for two other combat-specific controls 
as well as using a different config for arrow buttons as the primary movement controls.

## Pogoing
A pogo is done by hitting the top of a platform with a downward attack.
While you're in the air:
1. Position yourself above a platform
2. Hold `S`;
3. Press `J` before landing

The timing can be a bit tricky, but if you time it well, you'll bounce upward.
It's useful right now for reaching platforms that are too high for a normal jump

# Getting Started

## Requirements
- C++20
- Cmake
- Git

## Clone the repo
```
git clone https://github.com/Semilore317/one-front.git 
cd one-front
```

## Configure the project
```
cmake -S . -B build
```

## Build
```
cmake --build build
```

then run the generated executable in the build directory

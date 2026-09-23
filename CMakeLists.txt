cmake_minimum_required(VERSION 4.2)

project(OneFront LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(raylib)

add_library(
    OneFrontCore
    game/game.cpp
    game/controls.cpp
    world/world.cpp
    world/player/player.cpp
    world/platform/platform.cpp
    rendering/draw_player.cpp
)

add_executable(
    OneFront
    main.cpp
)

target_link_libraries(
    OneFrontCore
    PUBLIC
    raylib
)

target_link_libraries(OneFront
    PRIVATE
    OneFrontCore
)

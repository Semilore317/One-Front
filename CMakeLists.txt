cmake_minimum_required(VERSION 4.2)

project(OneFront LANGUAGES C CXX)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(raylib)

add_executable(OneFront main.cpp rendering/draw_player.cpp game/game.cpp world/player/player.cpp)
target_compile_features(OneFront PRIVATE cxx_std_23)
target_link_libraries(OneFront PRIVATE raylib)

set(CMAKE_CXX_STANDARD 23)

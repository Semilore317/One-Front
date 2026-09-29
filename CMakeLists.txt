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
    game/camera/game_camera.cpp
    game/controls.cpp
    game/goal.cpp
    world/level/level_builder.cpp
    world/world.cpp
    world/levels/vertical_prototype.cpp
    world/player/player.cpp
    world/platform/platform.cpp
    rendering/draw_goal.cpp
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

target_include_directories(
    OneFrontCore
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(OneFront
    PRIVATE
    OneFrontCore
)

include(CTest)

if(BUILD_TESTING)
    add_executable(
        OneFrontCameraTests
        tests/game_camera_tests.cpp
    )

    add_executable(
        OneFrontWorldLayoutTests
        tests/world_layout_tests.cpp
    )

    add_executable(
        OneFrontLevelBuilderTests
        tests/level_builder_tests.cpp
    )

    add_executable(
        OneFrontPlayerContactTests
        tests/player_contact_tests.cpp
    )

    add_executable(
        OneFrontGoalTests
        tests/goal_tests.cpp
    )

    target_link_libraries(
        OneFrontCameraTests
        PRIVATE
        OneFrontCore
    )

    target_link_libraries(
        OneFrontWorldLayoutTests
        PRIVATE
        OneFrontCore
    )

    target_link_libraries(
        OneFrontLevelBuilderTests
        PRIVATE
        OneFrontCore
    )

    target_link_libraries(
        OneFrontPlayerContactTests
        PRIVATE
        OneFrontCore
    )

    target_link_libraries(
        OneFrontGoalTests
        PRIVATE
        OneFrontCore
    )

    add_test(NAME game_camera COMMAND OneFrontCameraTests)
    add_test(NAME level_builder COMMAND OneFrontLevelBuilderTests)
    add_test(NAME world_layout COMMAND OneFrontWorldLayoutTests)
    add_test(NAME player_contact COMMAND OneFrontPlayerContactTests)
    add_test(NAME goal COMMAND OneFrontGoalTests)
endif()

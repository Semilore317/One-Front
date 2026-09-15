#include <raylib.h>

int main() {
    InitWindow(1336, 768, "One Front");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(Color(22, 31, 40, 255));
        DrawText("One Front", 30, 30, 32, RAYWHITE);

        // temporary ground
        DrawRectangle(0, 520, 1100, 100, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
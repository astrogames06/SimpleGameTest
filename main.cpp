#include "raylib.h"
#include <cmath>
#include <cstdlib>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Shrinking + Energy Orbs");

    Vector2 position = { screenWidth / 2.0f, screenHeight / 2.0f };
    float radius = 30.0f;
    float shrinkRate = 0.1f;
    float restoreAmount = 10.0f;

    Vector2 orb = { static_cast<float>(GetRandomValue(50, screenWidth - 50)),
                    static_cast<float>(GetRandomValue(50, screenHeight - 50)) };
    float orbRadius = 10.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float speed = IsKeyDown(KEY_SPACE) ? 2.0f : 5.0f;
        float currentShrink = IsKeyDown(KEY_SPACE) ? shrinkRate * 0.2f : shrinkRate;

        if (IsKeyDown(KEY_RIGHT)) position.x += speed;
        if (IsKeyDown(KEY_LEFT)) position.x -= speed;
        if (IsKeyDown(KEY_UP)) position.y -= speed;
        if (IsKeyDown(KEY_DOWN)) position.y += speed;

        // Shrink logic
        radius -= currentShrink;
        if (radius < 5.0f) radius = 5.0f;

        // Collision with orb
        float dist = Vector2Distance(position, orb);
        if (dist < radius + orbRadius) {
            radius += restoreAmount;
            orb = { static_cast<float>(GetRandomValue(50, screenWidth - 50)),
                    static_cast<float>(GetRandomValue(50, screenHeight - 50)) };
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Move: Arrows | Hold SPACE = slow shrink + slow move", 10, 10, 20, GRAY);
            DrawText("Collect red orbs to grow!", 10, 35, 20, GRAY);
            DrawCircleV(orb, orbRadius, RED);
            DrawCircleV(position, radius, DARKBLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

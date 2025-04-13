#include "raylib.h"
#include <cmath>

Vector2 GenerateOrb(Vector2 playerPos, int screenWidth, int screenHeight, float minDist = 100.0f) {
    Vector2 orb;
    do {
        orb = { static_cast<float>(GetRandomValue(50, screenWidth - 50)),
                static_cast<float>(GetRandomValue(50, screenHeight - 50)) };
    } while (Vector2Distance(orb, playerPos) < minDist);
    return orb;
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Enhanced Shrinking Bot");

    Vector2 position = { screenWidth / 2.0f, screenHeight / 2.0f };
    float radius = 30.0f;
    float shrinkRate = 0.1f;
    float restoreAmount = 10.0f;
    float orbRadius = 10.0f;
    int score = 0;
    bool gameOver = false;

    Vector2 orb = GenerateOrb(position, screenWidth, screenHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!gameOver) {
            float speed = IsKeyDown(KEY_SPACE) ? 2.0f : 5.0f;
            float currentShrink = IsKeyDown(KEY_SPACE) ? shrinkRate * 0.2f : shrinkRate;

            if (IsKeyDown(KEY_RIGHT)) position.x += speed;
            if (IsKeyDown(KEY_LEFT)) position.x -= speed;
            if (IsKeyDown(KEY_UP)) position.y -= speed;
            if (IsKeyDown(KEY_DOWN)) position.y += speed;

            // Shrinking
            radius -= currentShrink;
            if (radius < 5.0f) {
                gameOver = true;
            }

            // Orb collision
            if (Vector2Distance(position, orb) < radius + orbRadius) {
                radius += restoreAmount;
                score++;
                orb = GenerateOrb(position, screenWidth, screenHeight);
            }
        } else {
            if (IsKeyPressed(KEY_R)) {
                // Reset game
                position = { screenWidth / 2.0f, screenHeight / 2.0f };
                radius = 30.0f;
                score = 0;
                orb = GenerateOrb(position, screenWidth, screenHeight);
                gameOver = false;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!gameOver) {
                DrawText("Move: Arrows | SPACE = shrink shield (slows move)", 10, 10, 20, GRAY);
                DrawText(TextFormat("Radius: %.1f", radius), 10, 35, 20, GRAY);
                DrawText(TextFormat("Score: %d", score), 10, 60, 20, GRAY);
                DrawCircleV(orb, orbRadius, RED);
                DrawCircleV(position, radius, DARKBLUE);
            } else {
                DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 30, 40, RED);
                DrawText(TextFormat("Final Score: %d", score), screenWidth / 2 - 80, screenHeight / 2 + 20, 20, DARKGRAY);
                DrawText("Press R to restart", screenWidth / 2 - 80, screenHeight / 2 + 50, 20, GRAY);
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

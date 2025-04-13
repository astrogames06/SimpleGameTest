#include <iostream>
#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main(void)
{
    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            if (GuiButton((Rectangle){ 100, 100, 100, 30 }, "Click me"))
            {
                std::cout << "Clicked!\n";
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
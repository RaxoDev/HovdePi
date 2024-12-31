#include <raylib.h>
#include "keyboard.h"

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    Keyboard keyboard(screenWidth);
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        //keyboard.Update();
        
        BeginDrawing();
            ClearBackground(darkGreen);
            keyboard.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}
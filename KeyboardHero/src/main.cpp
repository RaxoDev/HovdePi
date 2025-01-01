#include <raylib.h>
#include "keyboard.h"
#include <RtMidi.h>
#include "KeyboardInput.h"

// Function to handle MIDI messages
void midiCallback(double deltaTime, std::vector<unsigned char> *message, void *userData) {
    if (message->size() >= 3) {
        // MIDI message structure: [status, note, velocity]
        int status = message->at(0);
        int note = message->at(1);
        int velocity = message->at(2);

        if ((status & 0xF0) == 0x90 && velocity > 0) { // Note On
            std::cout << "Note On: " << note << " Velocity: " << velocity << std::endl;
        } else if ((status & 0xF0) == 0x80 || (status & 0xF0) == 0x90 && velocity == 0) { // Note Off
            std::cout << "Note Off: " << note << std::endl;
        }
    }
}

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    Keyboard keyboard(screenWidth);
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    // Initialize KeyboardInput
    KeyboardInput keyboard;
    if (!keyboard.init()) {
        return 1; // Exit if MIDI initialization fails
    }

    
    while (!WindowShouldClose())
    {
        //keyboard.Update();
        
        BeginDrawing();
            ClearBackground(darkGreen);
            keyboard.Draw();

            // Get the current note and velocity
            int note = keyboard.getLastNote();
            int velocity = keyboard.getVelocity();

            if (note != -1) {
                DrawText(TextFormat("Last Note: %d", note), 10, 10, 20, DARKGREEN);
                DrawText(TextFormat("Velocity: %d", velocity), 10, 40, 20, DARKBLUE);
            } else {
                DrawText("No note playing...", 10, 10, 20, GRAY);
            }
        EndDrawing();
    }
    
    CloseWindow();
}
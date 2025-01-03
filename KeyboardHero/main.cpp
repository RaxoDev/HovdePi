// main.cpp
#include <SDL2/SDL.h>
#include "keyboard_input.hpp"
#include "midi_event.hpp"
#include "key.hpp"
#include "keyboard.hpp"
#include <queue>
#include <iostream>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int FRAME_DELAY = 16; // ~60 FPS (1000ms / 60 = ~16ms)

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Keyboard Hero",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Game loop variables
    bool isRunning = true;
    SDL_Event event;

    // Initialize the keyboard input
    KeyboardInput keyboardInput;
    if (!keyboardInput.init()) {
        std::cerr << "Failed to initialize MIDI input" << std::endl;
        return -1;
    }

    Keyboard keyboard(SCREEN_WIDTH, SCREEN_HEIGHT);  // Create a keyboard with a screen width and height


    // Game loop
    while (isRunning) {
        Uint32 frameStart = SDL_GetTicks(); // Record when the frame started

        // 1. Handle Events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false; // Exit the game
            }
        }

        // 2. Update Game Logic
        // (Put your game logic here: move objects, check collisions, etc.)
        // For example: moving a rectangle
        // Process events from the queue
        while (keyboardInput.hasEvents()) {
            MidiEvent midiEvent = keyboardInput.popEvent();

            if (midiEvent.getType() == MidiEventType::NOTE_ON) {
                std::cout << "Note On: " << midiEvent.getMidiNote() << " \tVelocity: " << midiEvent.getVelocity() << std::endl;
            } else if (midiEvent.getType() == MidiEventType::NOTE_OFF) {
                std::cout << "Note Off: " << midiEvent.getMidiNote() << std::endl;
            }

            keyboard.Update(midiEvent);
        }

        // 3. Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear to black
        SDL_RenderClear(renderer);

        // Example: Draw a red rectangle
        //SDL_Rect rect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        //SDL_RenderFillRect(renderer, &rect);


        keyboard.Draw(renderer);
        
        SDL_RenderPresent(renderer); // Show the rendered frame

        // 4. Control Frame Rate
        Uint32 frameTime = SDL_GetTicks() - frameStart; // Calculate how long the frame took
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime); // Delay to maintain consistent frame rate
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

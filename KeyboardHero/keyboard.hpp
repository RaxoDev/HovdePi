#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include "key.hpp"
#include "keyboard_input.hpp"

class Keyboard {
public:
    Keyboard(int screenWidth, int screenHeight);  // Initialize the keyboard
    void Update(const MidiEvent& midiEvent);  // Update based on MIDI input
    void Draw(SDL_Renderer* renderer) const;  // Draw the keyboard

private:
    bool isBlackKey(int key) const;  // Check if the key is black
    std::unordered_map<int, Key> whiteKeys;  // Store white keys
    std::unordered_map<int, Key> blackKeys;  // Store black keys
    float width, height;
    int startKey, keyCount, whiteKeyCount;
};

#endif

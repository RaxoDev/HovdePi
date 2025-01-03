#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "key.hpp"
#include "keyboard_input.hpp"

class Keyboard {
public:
    Keyboard(float screenWidth, float screenHeight);  // Initialize the keyboard
    void Update(const MidiEvent& midiEvent);  // Update based on MIDI input
    void Draw(sf::RenderWindow& window) const;  // Draw the keyboard

private:
    bool isBlackKey(int key) const;  // Check if the key is black
    std::unordered_map<int, Key> whiteKeys;  // Store white keys
    std::unordered_map<int, Key> blackKeys;  // Store black keys
    float width, height;
    int startKey, keyCount, whiteKeyCount;
};

#endif

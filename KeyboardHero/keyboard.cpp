#include "keyboard.hpp"
#include <iostream>

inline bool Keyboard::isBlackKey(int key) const {
    return key % 12 == 1 || key % 12 == 3 || key % 12 == 6 || key % 12 == 8 || key % 12 == 10;
}

Keyboard::Keyboard(float width)
    : width(width), height(width / 8), startKey(21), keyCount(88) {
    
    // Calculate the number of white keys
    whiteKeyCount = 0;
    for (int i = startKey; i < startKey + keyCount; i++) {
        if (!isBlackKey(i)) {
            whiteKeyCount++;
        }
    }

    // Create white keys
    whiteKeys.clear();
    float x = 0;
    float y = 600 - height;
    const float whiteKeyWidth = width / whiteKeyCount;
    const float blackKeyWidth = whiteKeyWidth * 0.6f;

    for (int i = 0; i < whiteKeyCount; i++) {
        whiteKeys.insert({i, Key(i, x, y, whiteKeyWidth, height, sf::Color::White)});
        x += whiteKeyWidth;
    }

    // Create black keys
    blackKeys.clear();
    x = -blackKeyWidth * 0.5f;
    y = 600 - height;
    const float blackKeyHeight = height * 0.6f;
    for (int i = startKey; i < startKey + keyCount; i++) {
        if (isBlackKey(i)) {
            blackKeys.insert({i, Key(i, x, y, blackKeyWidth, blackKeyHeight, sf::Color::Black)});
        } else {
            x += whiteKeyWidth;
        }
    }
}

void Keyboard::Update(const KeyboardInput& keyboardInput) {
    // Get the last note pressed
    int lastNote = keyboardInput.getLastNote();

    // Change key colors based on the MIDI input
    for (auto& pair : whiteKeys) {
        if (pair.first == lastNote) {
            pair.second.SetColor(sf::Color::Red);
        } else {
            pair.second.SetColor(sf::Color::White);
        }
    }

    for (auto& pair : blackKeys) {
        if (pair.first == lastNote) {
            pair.second.SetColor(sf::Color::Red);
        } else {
            pair.second.SetColor(sf::Color::Black);
        }
    }
}

void Keyboard::Draw(sf::RenderWindow& window) const {
    // Draw white keys
    for (const auto& pair : whiteKeys) {
        pair.second.Draw(window);
    }

    // Draw black keys
    for (const auto& pair : blackKeys) {
        pair.second.Draw(window);
    }
}

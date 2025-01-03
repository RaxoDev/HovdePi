#include "keyboard.hpp"
#include <iostream>

inline bool Keyboard::isBlackKey(int key) const {
    return key % 12 == 1 || key % 12 == 3 || key % 12 == 6 || key % 12 == 8 || key % 12 == 10;
}

Keyboard::Keyboard(float screenWidth, float screenHeight)
    : width(screenWidth), height(width / 8), startKey(21), keyCount(88) {
    
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
    float y = screenHeight - height;
    const float whiteKeyWidth = width / whiteKeyCount;
    const float blackKeyWidth = whiteKeyWidth * 0.6f;

    for (int i = startKey; i < startKey + keyCount; i++) {
        if (!isBlackKey(i)) {
            whiteKeys.emplace(i, Key(i, x, y, whiteKeyWidth, height, {255, 255, 255, 255}));
            x += whiteKeyWidth;
        }
    }

    // Create black keys
    blackKeys.clear();
    x = -blackKeyWidth * 0.5f;
    y = screenHeight - height;
    const float blackKeyHeight = height * 0.6f;
    for (int i = startKey; i < startKey + keyCount; i++) {
        if (isBlackKey(i)) {
            blackKeys.emplace(i, Key(i, x, y, blackKeyWidth, blackKeyHeight, {0, 0, 0, 255}));
        } else {
            x += whiteKeyWidth;
        }
    }
}

void Keyboard::Update(const MidiEvent& midiEvent) {
    int midiNote = midiEvent.getMidiNote();

    if (midiEvent.getType() == MidiEventType::NOTE_ON) {
        if (isBlackKey(midiNote)) {
            if (blackKeys.count(midiNote))
                blackKeys[midiNote].SetColor({255, 0, 0, 255}); // Highlight pressed black key
        } else {
            if (whiteKeys.count(midiNote))
                whiteKeys[midiNote].SetColor({255, 0, 0, 255}); // Highlight pressed white key
        }
    }
    
    else if (midiEvent.getType() == MidiEventType::NOTE_OFF) {
        if (isBlackKey(midiNote)) {
            if (blackKeys.count(midiNote))
                blackKeys[midiNote].SetColor({0, 0, 0, 255}); // Reset to default
        } else {
            if (whiteKeys.count(midiNote))
                whiteKeys[midiNote].SetColor({255, 255, 255, 255}); // Reset to default
        }
    }
}


void Keyboard::Draw(SDL_Renderer* renderer) const {
    // Draw white keys
    for (const auto& pair : whiteKeys) {
        pair.second.Draw(renderer);
    }

    // Draw black keys
    for (const auto& pair : blackKeys) {
        pair.second.Draw(renderer);
    }
}

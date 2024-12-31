#include "keyboard.h"
#include "key.h"
#include <raylib.h>

inline bool isBlackKey(int key)
{
    return key % 12 == 1 || key % 12 == 3 || key % 12 == 6 || key % 12 == 8 || key % 12 == 10;
}

Keyboard::Keyboard(float width) 
    : width(width)
    , height(width / 8)
    , startKey(21)
    , keyCount(88)
{
    whiteKeyCount = 0;
    for (int i = startKey; i < startKey + keyCount; i++) {
        if (!isBlackKey(i)) {
            whiteKeyCount++;
        }
    }

    // create white keys
    whiteKeys = std::unordered_map<int, Key>();
    float x = 0;
    float y = 600 - height;
    const float whiteKeyWidth = width / whiteKeyCount;
    const float blackKeyWidth = whiteKeyWidth * 0.6f;

    for (int i = 0; i < whiteKeyCount; i++) {
        
        whiteKeys.insert({i, Key(i, x, y, whiteKeyWidth, height, WHITE)});
        x += whiteKeyWidth;
    }

    // create black keys
    blackKeys = std::unordered_map<int, Key>();
    x = -blackKeyWidth * 0.5f;
    y = 600 - height;
    const float blackKeyHeight = height * 0.6f;
    for (int i = startKey; i < startKey + keyCount; i++) {
        if (isBlackKey(i)) {
            blackKeys.insert({i, Key(i, x, y, blackKeyWidth, blackKeyHeight, BLACK)});
        }
        else {
            x += whiteKeyWidth;
        }
    }
}

void Keyboard::Update() 
{
    
}

void Keyboard::Draw() const
{
    // draw white keys
    for (const auto& pair : whiteKeys) {
        pair.second.Draw();
    }

    // draw black keys
    for (const auto& pair : blackKeys) {
        pair.second.Draw();
    }
}
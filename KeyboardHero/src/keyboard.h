#pragma once

#include <unordered_map>
#include "key.h"

class Keyboard
{
public:
    Keyboard(float width);
    void Update();
    void Draw() const;

private:
    float width;
    float height;
    int startKey;
    int keyCount;
    int whiteKeyCount;
    std::unordered_map<int, Key> whiteKeys;
    std::unordered_map<int, Key> blackKeys;
};
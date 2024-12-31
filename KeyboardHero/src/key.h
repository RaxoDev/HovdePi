#pragma once

#include "raylib.h"

class Key
{
public:
    Key(int midiNote, float x, float y, float width, float height, Color color);
    void Update();
    void Draw() const;

private:
    int midiNote;
    float x;
    float y;
    float width;
    float height;
    Color color;
};
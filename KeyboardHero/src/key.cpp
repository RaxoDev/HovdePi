#include "key.h"
#include <raylib.h>

Key::Key(int midiNote, float x, float y, float width, float height, Color color) 
    :midiNote(midiNote), x(x), y(y), width(width), height(height), color(color)
{
}

void Key::Update() 
{
    
}

void Key::Draw() const
{
    DrawRectangle(x, y, width, height, color);
    DrawRectangleLines(x, y, width, height, GRAY);
}
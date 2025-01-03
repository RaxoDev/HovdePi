#include "key.hpp"

Key::Key()
    : midiNote(-1), x(0), y(0), width(0), height(0), color({255, 255, 255, 255}) {}

Key::Key(int midiNote, int x, int y, int width, int height, SDL_Color color)
    : midiNote(midiNote), x(x), y(y), width(width), height(height), color(color) {}

void Key::Update() {
    // Logic for updating the key can go here
}

void Key::Draw(SDL_Renderer* renderer) const {
    // Set fill color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Create and fill the rectangle
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);

    // Set outline color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black outline

    // Draw the rectangle outline
    SDL_RenderDrawRect(renderer, &rect);
}

void Key::SetColor(const SDL_Color &newColor) {
    color = newColor;
}

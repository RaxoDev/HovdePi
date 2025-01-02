#include "key.hpp"

Key::Key(int midiNote, float x, float y, float width, float height, sf::Color color)
    : midiNote(midiNote), x(x), y(y), width(width), height(height), color(color) {}

void Key::Update() {
    // Logic for updating the key can go here (e.g., MIDI changes)
}

void Key::Draw(sf::RenderWindow &window) const {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(color);
    rectangle.setOutlineColor(sf::Color::Black); // Outline for clarity
    rectangle.setOutlineThickness(1.0f);

    window.draw(rectangle);
}

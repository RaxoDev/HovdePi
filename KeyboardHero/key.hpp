#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>  // Include SFML for sf::Color

class Key {
public:
    Key(int midiNote, float x, float y, float width, float height, sf::Color color);
    void Update();
    void Draw(sf::RenderWindow &window) const; // Pass window to draw in SFML

private:
    int midiNote;
    float x, y, width, height;
    sf::Color color; // Use sf::Color instead of raylib's Color
};

#endif // KEY_HPP

#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>

class Key {
public:
    Key(int midiNote, float x, float y, float width, float height, sf::Color color);
    void Update();
    void Draw(sf::RenderWindow &window) const;
    void SetColor(const sf::Color &newColor); // Add this method

private:
    int midiNote;
    float x, y, width, height;
    sf::Color color;
};

#endif // KEY_HPP

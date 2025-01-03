#ifndef KEY_HPP
#define KEY_HPP

#include <SDL2/SDL.h>

class Key {
public:
    Key();
    Key(int midiNote, float x, float y, float width, float height, SDL_Color color);
    void Update();
    void Draw(SDL_Renderer* renderer) const;
    void SetColor(const SDL_Color &newColor); // Add this method

private:
    int midiNote;
    float x, y, width, height;
    SDL_Color color;
};

#endif // KEY_HPP

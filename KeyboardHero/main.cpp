#include <SFML/Graphics.hpp>
#include "keyboard.hpp"
#include "keyboard_input.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Piano");
    Keyboard keyboard(800.0f);
    KeyboardInput midiInput;

    if (!midiInput.init()) {
        return -1; // Exit if MIDI initialization fails
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Check for MIDI input
        int lastNote = midiInput.getLastNote();
        int velocity = midiInput.getVelocity();

        if (lastNote != -1 && velocity > 0) {
            keyboard.Update(lastNote, true); // Highlight the pressed key
        } else if (lastNote != -1 && velocity == 0) {
            keyboard.Update(lastNote, false); // Reset the released key
        }

        window.clear(sf::Color::Black);

        // Draw the keyboard
        keyboard.Draw(window);

        window.display();
    }

    return 0;
}

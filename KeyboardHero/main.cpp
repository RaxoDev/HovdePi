#include <SFML/Graphics.hpp>
#include "keyboard_input.hpp"
#include "keyboard.hpp"

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML MIDI Keyboard");

    // Initialize the MIDI input
    KeyboardInput keyboardInput;
    if (!keyboardInput.init()) {
        std::cerr << "Failed to initialize MIDI input!" << std::endl;
        return -1;
    }

    // Create the keyboard object (set width to 800)
    Keyboard keyboard(800.0f);

    // Main application loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the keyboard's key colors based on MIDI input
        keyboard.Update(keyboardInput);

        // Clear the window and draw the keyboard
        window.clear();
        keyboard.Draw(window);
        window.display();
    }

    return 0;
}

// main.cpp
#include <SFML/Graphics.hpp>
#include "keyboard_input.hpp"
#include "midi_event.hpp"
#include "key.hpp"
#include "keyboard.hpp"
#include <queue>
#include <iostream>

int main() {
    // Initialize your SFML window and other resources
    sf::RenderWindow window(sf::VideoMode(800, 600), "Keyboard Hero");

    // Initialize the keyboard input
    KeyboardInput keyboardInput;
    if (!keyboardInput.init()) {
        std::cerr << "Failed to initialize MIDI input" << std::endl;
        return -1;
    }

    Keyboard keyboard(800);  // Create a keyboard with a certain width

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Process events from the queue
        while (keyboardInput.hasEvents()) {
            MidiEvent midiEvent = keyboardInput.popEvent();

            if (midiEvent.getType() == MidiType::NoteOn) {
                std::cout << "Note On: " << getMidiNote() << std::endl;
                // You can add logic here to change the color or state of keys based on midiEvent.note
                // For example, you could change a key's color when it is pressed
            } else if (midiEvent.getType() == MidiType::NoteOff) {
                std::cout << "Note Off: " << getMidiNote() << std::endl;
                // Handle note-off logic, e.g., reset the key color
            }
            keyboard.Update(midiEvent);
        }

        // Clear the window
        window.clear();

        // Update and draw the keyboard
        keyboard.Draw(window);

        // Display the window
        window.display();
    }

    return 0;
}

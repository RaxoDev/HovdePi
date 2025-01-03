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
    int width = 1920;
    int height = 1080;

    sf::RenderWindow window(sf::VideoMode(width, height), "Keyboard Hero");

    // Initialize the keyboard input
    KeyboardInput keyboardInput;
    if (!keyboardInput.init()) {
        std::cerr << "Failed to initialize MIDI input" << std::endl;
        return -1;
    }

    Keyboard keyboard(width);  // Create a keyboard with a certain width

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Process events from the queue
        while (keyboardInput.hasEvents()) {
            MidiEvent midiEvent = keyboardInput.popEvent();

            if (midiEvent.getType() == MidiEventType::NOTE_ON) {
                std::cout << "Note On: " << midiEvent.getMidiNote() << " \tVelocity: " << midiEvent.getVelocity() << std::endl;
            } else if (midiEvent.getType() == MidiEventType::NOTE_OFF) {
                std::cout << "Note Off: " << midiEvent.getMidiNote() << std::endl;
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

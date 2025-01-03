#include "keyboard_input.hpp"
#include <iostream>

KeyboardInput::KeyboardInput() : midiIn(nullptr) {}

KeyboardInput::~KeyboardInput() {
    if (midiIn) {
        midiIn->closePort();
        delete midiIn;
    }
}

bool KeyboardInput::init() {
    try {
        midiIn = new RtMidiIn();
        if (midiIn->getPortCount() == 0) {
            std::cerr << "No MIDI input devices available." << std::endl;
            return false;
        }

        // Open the first MIDI input device
        midiIn->openPort(1);
        midiIn->setCallback(&KeyboardInput::midiCallback, this);
        midiIn->ignoreTypes(false, false, false); // Don't ignore any message types

        std::cout << "MIDI Input initialized. Listening for keyboard input..." << std::endl;
        return true;
    } catch (RtMidiError& error) {
        std::cerr << "RtMidiError: " << error.getMessage() << std::endl;
        return false;
    }
}

void KeyboardInput::midiCallback(double deltaTime, std::vector<unsigned char>* message, void* userData) {
    auto* keyboard = static_cast<KeyboardInput*>(userData);

    if (message->size() >= 3) {
        int status = message->at(0);
        int note = message->at(1);
        int velocity = message->at(2);

        // Check for Note On or Note Off
        if ((status & 0xF0) == 0x90 && velocity > 0) {  // Note On
            MidiEvent event(MidiEventType::NOTE_ON, note, velocity);
            keyboard->eventQueue.push(event);
            std::cout << "Note On: " << note << " Velocity: " << velocity << std::endl;
        } else if ((status & 0xF0) == 0x80 || ((status & 0xF0) == 0x90 && velocity == 0)) {  // Note Off
            MidiEvent event(MidiEventType::NOTE_OFF, note, velocity);
            keyboard->eventQueue.push(event);
            std::cout << "Note Off: " << note << std::endl;
        }

        // Check for Control Change (Pedal events)
        else if ((status & 0xF0) == 0xB0) {  // Control Change message
            int controlNumber = message->at(1);
            int controlValue = message->at(2);

            // Sustain pedal (RIGHT) (CC 64)
            if (controlNumber == 64) {
                std::cout << "Sustain (RIGHT) Pedal: " << controlValue << std::endl;
            }
            // Soft Pedal (LEFT) (CC 67)
            else if (controlNumber == 67) {
                std::cout << "Soft (LEFT) Pedal: " << controlValue << std::endl;
            }
            // Sostenuto Pedal (MIDDLE) (CC 67)
            else if (controlNumber == 66) {
                std::cout << "Sostenuto (MIDDLE) Pedal: " << controlValue << std::endl;
            }
        }
    }
}

MidiEvent KeyboardInput::popEvent() {
    if (!eventQueue.empty()) {
        MidiEvent event = eventQueue.front();
        eventQueue.pop();
        return event;
    } else {
        // Return null if the queue is empty
        return NULL;
    }
}

bool KeyboardInput::hasEvents() const {
    return !eventQueue.empty();  // Return true if there are events in the queue
}


#include "KeyboardInput.h"
#include <iostream>

KeyboardInput::KeyboardInput() : midiIn(nullptr), lastNote(-1), velocity(0) {}

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
        midiIn->openPort(0);
        midiIn->setCallback(&KeyboardInput::midiCallback, this);
        midiIn->ignoreTypes(false, false, false); // Don't ignore any message types

        std::cout << "MIDI Input initialized. Listening for keyboard input..." << std::endl;
        return true;
    } catch (RtMidiError &error) {
        std::cerr << "RtMidiError: " << error.getMessage() << std::endl;
        return false;
    }
}

int KeyboardInput::getLastNote() const {
    return lastNote;
}

int KeyboardInput::getVelocity() const {
    return velocity;
}

void KeyboardInput::midiCallback(double deltaTime, std::vector<unsigned char> *message, void *userData) {
    auto *keyboard = static_cast<KeyboardInput *>(userData);

    if (message->size() >= 3) {
        int status = message->at(0);
        int note = message->at(1);
        int vel = message->at(2);

        if ((status & 0xF0) == 0x90 && vel > 0) { // Note On
            keyboard->lastNote = note;
            keyboard->velocity = vel;
            std::cout << "Note On: " << note << " Velocity: " << vel << std::endl;
        } else if ((status & 0xF0) == 0x80 || ((status & 0xF0) == 0x90 && vel == 0)) { // Note Off
            keyboard->lastNote = -1; // Reset the note
            keyboard->velocity = 0;
            std::cout << "Note Off: " << note << std::endl;
        }
    }
}

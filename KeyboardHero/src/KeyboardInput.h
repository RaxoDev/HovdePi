#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <vector>
#include <RtMidi.h>

class KeyboardInput {
public:
    KeyboardInput();
    ~KeyboardInput();

    // Initialize the MIDI input
    bool init();

    // Get the last note and velocity
    int getLastNote() const;
    int getVelocity() const;

private:
    RtMidiIn *midiIn;
    int lastNote;
    int velocity;

    // Callback function to handle incoming MIDI messages
    static void midiCallback(double deltaTime, std::vector<unsigned char> *message, void *userData);
};

#endif // KEYBOARDINPUT_H

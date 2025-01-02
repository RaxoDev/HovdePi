#ifndef KEYBOARD_INPUT_HPP
#define KEYBOARD_INPUT_HPP

#include <RtMidi.h>
#include <vector>

class KeyboardInput {
public:
    KeyboardInput();
    ~KeyboardInput();
    
    bool init();
    int getLastNote() const;
    int getVelocity() const;

    static void midiCallback(double deltaTime, std::vector<unsigned char> *message, void *userData);

private:
    RtMidiIn *midiIn;
    int lastNote;
    int velocity;
};

#endif

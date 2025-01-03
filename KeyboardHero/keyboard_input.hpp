#ifndef KEYBOARD_INPUT_HPP
#define KEYBOARD_INPUT_HPP

#include <RtMidi.h>
#include "midi_event.hpp"
#include <queue>
#include <vector>

class KeyboardInput {
public:
    KeyboardInput();
    ~KeyboardInput();
    
    bool init();
    std::queue<MidiEvent>& getEventQueue() { return eventQueue; }

    static void midiCallback(double deltaTime, std::vector<unsigned char> *message, void *userData);

private:
    RtMidiIn *midiIn;
    std::queue<MidiEvent> eventQueue;  // A queue to hold MIDI events
};

#endif

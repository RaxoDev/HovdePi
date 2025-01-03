#include "midi_event.hpp"
#include <iostream>

// This is optional, for debugging or logging
void MidiEvent::printEvent() const {
    std::string eventType = (type == MidiEventType::NOTE_ON) ? "Note On" : "Note Off";
    std::cout << eventType << " - MIDI Note: " << midiNote << " Velocity: " << velocity << std::endl;
}

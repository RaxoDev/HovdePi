#include <iostream>
#include "MidiFile.h" // Include the MidiFile library

using namespace smf;

int main() {
    // Load the MIDI file
    MidiFile midiFile;
    if (!midiFile.read("example.mid")) {
        std::cerr << "Failed to read MIDI file!" << std::endl;
        return 1;
    }

    // Convert ticks to real-time (seconds)
    midiFile.doTimeAnalysis();

    std::cout << "Number of tracks: " << midiFile.getTrackCount() << std::endl;

    // Iterate through each track
    for (int track = 0; track < midiFile.getTrackCount(); ++track) {
        std::cout << "Track " << track << ":\n";

        // Iterate through each event in the track
        for (int eventIndex = 0; eventIndex < midiFile[track].size(); ++eventIndex) {
            MidiEvent event = midiFile[track][eventIndex];

            // Check if it's a "Note On" event
            if (event.isNoteOn()) {
                int pitch = event.getKeyNumber();     // MIDI note number (0-127)
                int velocity = event.getVelocity();  // Velocity (0-127)
                double time = event.seconds;         // Time in seconds

                std::cout << "  Note On: Pitch=" << pitch
                          << " Velocity=" << velocity
                          << " Time=" << time << "s\n";
            }

            // Check if it's a "Note Off" event
            if (event.isNoteOff()) {
                int pitch = event.getKeyNumber(); // MIDI note number
                double time = event.seconds;     // Time in seconds

                std::cout << "  Note Off: Pitch=" << pitch
                          << " Time=" << time << "s\n";
            }
        }
    }

    return 0;
}
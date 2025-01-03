#ifndef MIDI_EVENT_HPP
#define MIDI_EVENT_HPP

enum class MidiEventType {
    NOTE_ON,
    NOTE_OFF
};

class MidiEvent {
public:
    MidiEvent(MidiEventType type, int midiNote, int velocity)
        : type(type), midiNote(midiNote), velocity(velocity) {}

    MidiEventType getType() const { return type; }
    int getMidiNote() const { return midiNote; }
    int getVelocity() const { return velocity; }

    void printEvent() const;

private:
    MidiEventType type;

    int midiNote;
    int velocity;
};

#endif // MIDI_EVENT_HPP

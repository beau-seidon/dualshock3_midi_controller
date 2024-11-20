#include "midi_handler.h"


MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, dinMIDI);

struct CustomBaudRateSettings : public MIDI_NAMESPACE::DefaultSerialSettings {
  static const long BaudRate = 115200;
};

MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial);
MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> usbMIDI((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>&)serialMIDI);


static byte active_midi_channel = DEFAULT_MIDI_CHANNEL;

static byte aftertouch_pressure[8] = {0};



void midi_setup() {
    usbMIDI.begin(MIDI_CHANNEL_OMNI);
    dinMIDI.begin(MIDI_CHANNEL_OMNI);
}


void midi_sendNoteOn(byte note_button, byte button_pressure) {
    byte note = get_note_from_button(note_button);
    byte velocity = (byte)map(button_pressure, 0, 255, 1, 127);
    usbMIDI.sendNoteOn(note, velocity, active_midi_channel);
    dinMIDI.sendNoteOn(note, velocity, active_midi_channel);
    set_active_notes(1);
}


void midi_sendNoteOff(byte note_button) {
    byte note = get_note_from_button(note_button);
    usbMIDI.sendNoteOff(note, 0, active_midi_channel);
    dinMIDI.sendNoteOff(note, 0, active_midi_channel);
    set_active_notes(-1);
}


static byte calculate_channel_aftertouch(byte note_button, byte button_pressure) {
    aftertouch_pressure[note_button] = button_pressure;
    byte active_channels = 0;
    byte total_pressure = 0;
    byte average_pressure = 0;
    for(byte i = 0; i < 8; i++) {
        if (aftertouch_pressure[i] > 0) {
            active_channels++;
            total_pressure += aftertouch_pressure[i];
        }
    }
    if (active_channels > 0) average_pressure = total_pressure / active_channels;
    return (byte)map(average_pressure, 0, 255, 0, 127);
}


void midi_sendAftertouch(byte note_button, byte button_pressure, int aftertouch_mode) {
    byte note = get_note_from_button(note_button);
    byte pressure;
    switch(aftertouch_mode) {
        case AT_MODE::KEY:
            pressure = (byte)map(button_pressure, 0, 255, 0, 127);
            usbMIDI.sendAfterTouch(note, pressure, active_midi_channel);        // key aftertouch
            dinMIDI.sendAfterTouch(note, pressure, active_midi_channel);        // key aftertouch
            break;
        case AT_MODE::CHANNEL:
            pressure = calculate_channel_aftertouch(note_button, button_pressure);
            usbMIDI.sendAfterTouch(pressure, active_midi_channel);              // channel aftertouch
            dinMIDI.sendAfterTouch(pressure, active_midi_channel);              // channel aftertouch
            break;
        default:
            break;
    }
}


void midi_sendCC(byte cc_number, int axis_value, bool invert_axis) {
    byte value;
    if (invert_axis)
        value = (byte)map(axis_value, 127, -128, 0, 127);
    else
        value = (byte)map(axis_value, -128, 127, 0, 127);
    usbMIDI.sendControlChange(cc_number, value, active_midi_channel);
    dinMIDI.sendControlChange(cc_number, value, active_midi_channel);
}


void midi_toggleCC(byte cc_number, bool active) {
    if (active) {
        usbMIDI.sendControlChange(cc_number, 127, active_midi_channel);
        dinMIDI.sendControlChange(cc_number, 127, active_midi_channel);
    } else {
        usbMIDI.sendControlChange(cc_number, 0, active_midi_channel);
        dinMIDI.sendControlChange(cc_number, 0, active_midi_channel);
    }
}


void midi_sendPitchBend(byte up_trigger_value, byte down_trigger_value) {
    int net_trigger_value = up_trigger_value - down_trigger_value;
    int bend = (int)map(net_trigger_value, -255, 255, MIDI_PITCHBEND_MIN, MIDI_PITCHBEND_MAX);
    usbMIDI.sendPitchBend(bend, active_midi_channel);
    dinMIDI.sendPitchBend(bend, active_midi_channel);
}


byte midi_get_active_channel() {
    return active_midi_channel;
}


void midi_change_channel(int increment) {
    byte new_channel = active_midi_channel;
    new_channel += increment;
    if (new_channel < 1) new_channel = 16;
    if (new_channel > 16) new_channel = 1;
    active_midi_channel = new_channel;
}


void midi_stop_all_notes() {
    for (int i = 0; i < 128; i++) {
        usbMIDI.sendNoteOff(i, 0, active_midi_channel);
        dinMIDI.sendNoteOff(i, 0, active_midi_channel);
        set_active_notes(-1);
    }
}

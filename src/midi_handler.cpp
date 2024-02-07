#include <midi_handler.h>



// MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, Serial2MIDI);

struct CustomBaudRateSettings : public MIDI_NAMESPACE::DefaultSerialSettings {
  static const long BaudRate = 115200;
};

#if defined(ARDUINO_SAM_DUE) || defined(USBCON) || defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
    // Leonardo, Due and other USB boards use Serial1 by default.
    MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial1);
    MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> MIDI((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>&)serialMIDI);
#else
    MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial);
    MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> SerialUsbMidi((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>&)serialMIDI);
#endif

#define Serial2MIDI SerialUsbMidi


static int active_midi_channel = DEFAULT_MIDI_CHANNEL;

static byte AfterTouch_pressure[8] = {0};



void midi_setup() 
{
    Serial2MIDI.begin(MIDI_CHANNEL_OMNI);
}



// void midi_test_transmit()
// {
//     digitalWrite(LED_BUILTIN, HIGH);
//     Serial2MIDI.sendNoteOn(42, 127, 1);     // Send a Note (pitch 42, velo 127 on channel 1)
//     delay(1000);		                    // Wait for a second
//     Serial2MIDI.sendNoteOff(42, 0, 1);      // Stop the note
//     digitalWrite(LED_BUILTIN, LOW);
// }



void midi_sendNoteOn(int note_button, byte button_pressure) 
{
    byte note = (byte)get_note_from_button(note_button);
    byte velocity = (byte)map(button_pressure, 0, 255, 1, 127);
    Serial2MIDI.sendNoteOn(note, velocity, active_midi_channel);
    set_active_notes(1);
}



void midi_sendNoteOff(int note_button) 
{
    byte note = (byte)get_note_from_button(note_button);
    Serial2MIDI.sendNoteOff(note, 0, active_midi_channel);
    set_active_notes(-1);
}



static byte calculate_ChannelAfterTouch(int note_button, int button_pressure)
{
    AfterTouch_pressure[note_button] = button_pressure;

    int active_channels = 0;
    int total_pressure = 0;
    int average_pressure = 0;
    for(int i = 0; i < 8; i++) {
        if (AfterTouch_pressure[i] > 0) {
            active_channels++;
            total_pressure += AfterTouch_pressure[i];
        }
    }
    if (active_channels > 0) average_pressure = total_pressure / active_channels;

    return (byte)map(average_pressure, 0, 255, 0, 127);
}



void midi_sendAftertouch(int note_button, byte button_pressure, bool key)
{
    byte note = (byte)get_note_from_button(note_button);
    
    byte pressure;
    if (key) {
        pressure = (byte)map(button_pressure, 0, 255, 0, 127);
        Serial2MIDI.sendAfterTouch(note, pressure, active_midi_channel);        // key aftertouch
    } else {
        pressure = calculate_ChannelAfterTouch(note_button, button_pressure);
        Serial2MIDI.sendAfterTouch(pressure, active_midi_channel);              // channel aftertouch
    }
}



void midi_sendCC(byte cc_number, int axis_value, bool invert_axis=false)
{
    byte value;
    if (invert_axis)
        value = map(axis_value, 127, -128, 0, 127);
    else
        value = map(axis_value, -128, 127, 0, 127);
    Serial2MIDI.sendControlChange(cc_number, value, active_midi_channel);
}



void midi_toggleCC(byte cc_number, bool active)
{
    if (active)
        Serial2MIDI.sendControlChange(cc_number, 127, active_midi_channel);
    else
        Serial2MIDI.sendControlChange(cc_number, 0, active_midi_channel);
}



void midi_sendPitchBend(int up_trigger_value, int down_trigger_value)
{
    int net_trigger_value = up_trigger_value - down_trigger_value;
    int bend = map(net_trigger_value, -255, 255, MIDI_PITCHBEND_MIN, MIDI_PITCHBEND_MAX);
    Serial2MIDI.sendPitchBend(bend, active_midi_channel);
}



int midi_get_active_channel()
{
    return active_midi_channel;
}



void midi_change_channel(int increment)
{
    int new_channel = active_midi_channel;
    new_channel += increment;
    if (new_channel < 1) new_channel = 16;
    if (new_channel > 16) new_channel = 1;
    active_midi_channel = new_channel;
}



void stop_all_notes()
{
    for (byte i = 0; i < 128; i++) {
        Serial2MIDI.sendNoteOff(i, 0, MIDI_CHANNEL_OMNI);
        set_active_notes(-1);
    }
}

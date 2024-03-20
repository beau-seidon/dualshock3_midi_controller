#pragma once

#include <Arduino.h>
#include <MIDI.h>
#include "config.h"
#include "note_handler.h"



const byte left_joystick_x_cc = 20;
const byte left_joystick_y_cc = 21;
const byte right_joystick_x_cc = 22;  
const byte right_joystick_y_cc = 23;

const byte left_shoulder_cc = 64;       // sustain
const byte right_shoulder_cc = 64;      // sustain

enum AT_MODE { NONE, KEY, CHANNEL };


void midi_setup(void);
byte midi_get_active_channel(void);
void midi_sendNoteOn(byte note_button, byte button_pressure);
void midi_sendNoteOff(byte note_button);
void midi_sendAftertouch(byte note_button, byte button_pressure, int aftertouch_mode);
void midi_sendCC(byte cc_number, int axis_value, bool invert_axis);
void midi_sendPitchBend(byte up_trigger_value, byte down_trigger_value);
void midi_change_channel(int increment);
void midi_toggleCC(byte cc_number, bool active);
void midi_stop_all_notes(void);

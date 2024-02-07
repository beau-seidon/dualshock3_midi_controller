#pragma once

#include <Arduino.h>
#include <Ps3Controller.h>
#include <config.h>



static const byte default_pressure = 202;   // about 80%, 

void ps3_setup(void);



// external: midi_handler
extern const byte left_joystick_x_cc;
extern const byte left_joystick_y_cc;
extern const byte right_joystick_x_cc;
extern const byte right_joystick_y_cc;
extern const byte left_bumper_toggle_cc;
extern const byte right_bumper_toggle_cc;

// void midi_test_transmit(void);
int midi_get_active_channel(void);
void midi_sendNoteOn(int note_button, byte button_pressure);
void midi_sendNoteOff(int note_button);
void midi_sendAftertouch(int note_button, byte button_pressure, bool key);
void midi_sendCC(byte cc_number, int axis_value, bool invert_axis);
void midi_sendPitchBend(int up_trigger_value, int down_trigger_value);
void midi_change_channel(int increment);
void midi_toggleCC(byte cc_number, bool active);

// external: note_handler
extern const int left_bumper_fine_transpose;
extern const int left_bumper_coarse_transpose;
extern const int right_bumper_fine_transpose;
extern const int right_bumper_coarse_transpose;

void initialize_notes(void);
void set_diatonic_mode(int new_mode);
void set_transpose(int adjust);

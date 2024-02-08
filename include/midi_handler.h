#pragma once

#include <Arduino.h>
#include <MIDI.h>
#include <config.h>



const byte left_joystick_x_cc = 20;
const byte left_joystick_y_cc = 21;
const byte right_joystick_x_cc = 22;  
const byte right_joystick_y_cc = 23;

const byte left_shoulder_cc = 64;       // sustain
const byte right_shoulder_cc = 64;      // sustain

void midi_setup(void);



/* external: note_handler */
int get_note_from_button(int button);
void set_active_notes(int adjust);

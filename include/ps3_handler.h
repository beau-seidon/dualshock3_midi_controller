#pragma once

#include <Arduino.h>
#include <Ps3Controller.h>
#include <config.h>



struct button_state {
    bool select = false;
    bool start = false;
    bool ps = false;

    bool L1 = false;
    bool L2 = false;
    bool R1 = false;
    bool R2 = false;
};

void ps3_setup(void);



/* external: midi_handler */
extern const byte left_joystick_x_cc;
extern const byte left_joystick_y_cc;
extern const byte right_joystick_x_cc;
extern const byte right_joystick_y_cc;
extern const byte left_shoulder_cc;
extern const byte right_shoulder_cc;

byte midi_get_active_channel(void);
void midi_sendNoteOn(byte note_button, byte button_pressure);
void midi_sendNoteOff(byte note_button);
void midi_sendAftertouch(byte note_button, byte button_pressure, bool key);
void midi_sendCC(byte cc_number, int axis_value, bool invert_axis);
void midi_sendPitchBend(byte up_trigger_value, byte down_trigger_value);
void midi_change_channel(int increment);
void midi_toggleCC(byte cc_number, bool active);
void midi_stop_all_notes(void);

/* external: note_handler */
extern const int left_bumper_fine_transpose;
extern const int left_bumper_coarse_transpose;
extern const int right_bumper_fine_transpose;
extern const int right_bumper_coarse_transpose;

void initialize_notes(void);
void set_diatonic_mode(int new_mode);
void set_transpose(int adjust);

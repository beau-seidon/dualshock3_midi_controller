#pragma once

#include <Arduino.h>
#include "config.h"
#include "note_names.h"
#include "diatonic_modes.h"
#include "midi_handler.h"



const int left_bumper_fine_transpose = -1;
const int left_bumper_coarse_transpose = -12;
const int right_bumper_fine_transpose = 1;
const int right_bumper_coarse_transpose = 12;


void initialize_notes(void);
void set_diatonic_mode(int new_mode);
int get_note_from_button(int button);
void set_active_notes(int adjust);
void set_transpose(int adjust);

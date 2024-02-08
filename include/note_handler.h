#pragma once

#include <Arduino.h>
#include <note_names.h>
#include <diatonic_modes.h>
#include <config.h>



const int left_bumper_fine_transpose = -1;
const int left_bumper_coarse_transpose = -12;
const int right_bumper_fine_transpose = 1;
const int right_bumper_coarse_transpose = 12;

void initialize_notes(void);


/* external: midi_handler */
void midi_stop_all_notes(void);

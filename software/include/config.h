#pragma once

#include <Arduino.h>



// determine using SixaxisPairTool
#define CURRENT_MASTER_MAC "1a:2b:3c:01:01:01"

// adjust button order to remap to different pattern of diatonic scale intervals
// e.g. minor scale intervals in order: I, ii, iii, IV, V, vi, vii, 8va
enum NOTE_BUTTON{ DOWN, UP, CROSS, LEFT, SQUARE, RIGHT, CIRCLE, TRIANGLE };

const byte DEFAULT_MIDI_CHANNEL = 16;

const byte DEFAULT_PRESSURE = 255;

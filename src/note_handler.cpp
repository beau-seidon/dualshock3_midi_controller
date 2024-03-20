#include "note_handler.h"



static DiatonicMode mode;
static const int *DEFAULT_DIATONIC_MODE = mode.ionian;
static const int DEFAULT_TONIC = NOTE_C_4;
static int diatonic_mode[8];

static const int NOTE_LOW_DEFAULT = DEFAULT_TONIC;
static const int NOTE_HIGH_DEFAULT = DEFAULT_TONIC + 12;
static const int TRANSPOSE_MAX = (127 - (NOTE_HIGH_DEFAULT - NOTE_LOW_DEFAULT)) - NOTE_LOW_DEFAULT;
static const int TRANSPOSE_MIN = 0 - NOTE_LOW_DEFAULT;
static int transpose = 0;

int active_notes = 0;



void set_notes(int tonic, const int *MODE) {
    for (int n = 0; n < 8; n++) {
        diatonic_mode[n] = tonic + MODE[n];
    }
}


void initialize_notes() {
    transpose = 0;
    set_notes(DEFAULT_TONIC, DEFAULT_DIATONIC_MODE);
    midi_stop_all_notes();
}


void set_diatonic_mode(int new_mode) {
    int tonic = diatonic_mode[0];
    switch (new_mode) {
        case 0:
            set_notes(tonic, mode.ionian);
            break;
        case 1:
            set_notes(tonic, mode.dorian);
            break;
        case 2:
            set_notes(tonic, mode.phrygian);
            break;
        case 3:
            set_notes(tonic, mode.lydian);
            break;
        case 4:
            set_notes(tonic, mode.mixolydian);
            break;
        case 5:
            set_notes(tonic, mode.aeolian);
            break;
        case 6:
            set_notes(tonic, mode.locrian);
            break;
        case 7:
            set_notes(tonic, mode.ionian);
            break;
        default:
            return;
    }
}


int get_note_from_button(int button) {
    return diatonic_mode[button];
}


void set_active_notes(int adjust) {
    active_notes += adjust;
    if(active_notes < 0) active_notes = 0;
}


void set_transpose(int adjust) {    // this was made overcomplicated by lack of sleep lol 
    if (active_notes) return;
    int previous_transpose = transpose;
    transpose += adjust;
    if (transpose > TRANSPOSE_MAX) transpose = TRANSPOSE_MAX;
    if (transpose < TRANSPOSE_MIN) transpose = TRANSPOSE_MIN;
 
    int tonic = diatonic_mode[0];
    for (int n = 0; n < 8; n++) {
        diatonic_mode[n] += (transpose - previous_transpose);
    }
}

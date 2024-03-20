#pragma once

#include <Arduino.h>
#include <Ps3Controller.h>
#include "config.h"
#include "note_handler.h"
#include "midi_handler.h"



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

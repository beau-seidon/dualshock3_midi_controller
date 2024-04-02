#include "ps3_handler.h"



static button_state pressed;

static int player = 0;
static int battery = 0;

static int aftertouch_mode = AT_MODE::NONE;
static byte velocity_pressure = DEFAULT_PRESSURE;



static void toggle_aftertouch_mode() {
    if (aftertouch_mode >= AT_MODE::CHANNEL)
        aftertouch_mode = AT_MODE::NONE;
    else
        aftertouch_mode++;
}


static void set_velocity(byte pressure) {
    velocity_pressure = max((255 - pressure), 1);
}


static void ps3_midi_translate() {
/* Digital D-pad button events */
    if (Ps3.event.button_down.up) {
        if (pressed.ps) {
            set_diatonic_mode(NOTE_BUTTON::UP);
        } else {
            midi_sendNoteOn(NOTE_BUTTON::UP, velocity_pressure);
        }
    }

    if (Ps3.event.button_up.up)
        midi_sendNoteOff(NOTE_BUTTON::UP);


    if (Ps3.event.button_down.right) {
        if (pressed.ps) {
            set_diatonic_mode(NOTE_BUTTON::RIGHT);
        } else {
            midi_sendNoteOn(NOTE_BUTTON::RIGHT, velocity_pressure);
        }
    } 

    if (Ps3.event.button_up.right)
        midi_sendNoteOff(NOTE_BUTTON::RIGHT);


    if (Ps3.event.button_down.down) {
        if (pressed.ps) {
            set_diatonic_mode(NOTE_BUTTON::DOWN);
        } else {
            midi_sendNoteOn(NOTE_BUTTON::DOWN, velocity_pressure);
        }
    }

    if (Ps3.event.button_up.down)
        midi_sendNoteOff(NOTE_BUTTON::DOWN);


    if (Ps3.event.button_down.left) {
        if (pressed.ps) {
            set_diatonic_mode(NOTE_BUTTON::LEFT);
        } else {
            midi_sendNoteOn(NOTE_BUTTON::LEFT, velocity_pressure);
        }
    }

    if (Ps3.event.button_up.left)
        midi_sendNoteOff(NOTE_BUTTON::LEFT);


/* Digital shape button events */
    if (Ps3.event.button_down.cross) {
        if (pressed.ps) {
            set_diatonic_mode(NOTE_BUTTON::CROSS);
        } else {
            midi_sendNoteOn(NOTE_BUTTON::CROSS, velocity_pressure);
        }
    }

    if (Ps3.event.button_up.cross)
        midi_sendNoteOff(NOTE_BUTTON::CROSS);


    if (Ps3.event.button_down.square) {
        if (pressed.ps) {
            set_diatonic_mode(NOTE_BUTTON::SQUARE);
        } else {
            midi_sendNoteOn(NOTE_BUTTON::SQUARE, velocity_pressure);
        }
    }

    if (Ps3.event.button_up.square)
        midi_sendNoteOff(NOTE_BUTTON::SQUARE);


    if (Ps3.event.button_down.triangle) {
        if (pressed.ps) {
            set_diatonic_mode(NOTE_BUTTON::TRIANGLE);
        } else {
            midi_sendNoteOn(NOTE_BUTTON::TRIANGLE, velocity_pressure);
        }
    }

    if (Ps3.event.button_up.triangle)
        midi_sendNoteOff(NOTE_BUTTON::TRIANGLE);


    if (Ps3.event.button_down.circle) {
        if (pressed.ps) {
            set_diatonic_mode(NOTE_BUTTON::CIRCLE);
        } else {
            midi_sendNoteOn(NOTE_BUTTON::CIRCLE, velocity_pressure);
        }
    }

    if (Ps3.event.button_up.circle)
        midi_sendNoteOff(NOTE_BUTTON::CIRCLE);


/* Digital shoulder button events */
    if (Ps3.event.button_down.l1) {
        if (pressed.ps) 
            midi_change_channel(-1);
        else {
            pressed.L1 = true;
        }
    }

    if (Ps3.event.button_up.l1)
        pressed.L1 = false;
    

    if (Ps3.event.button_down.r1) {
        if (pressed.ps) 
            midi_change_channel(1);
        else {
            pressed.R1 = true;
            midi_toggleCC(right_shoulder_cc, true);
        }
    }

    if (Ps3.event.button_up.r1) {
        pressed.R1 = false; 
        midi_toggleCC(right_shoulder_cc, false);
    }


/* Digital trigger button events */
    if (Ps3.event.button_down.l2) {}

    if (Ps3.event.button_up.l2) {}


    if (Ps3.event.button_down.r2) {}

    if (Ps3.event.button_up.r2) {}


/* Digital stick button events */
    if (Ps3.event.button_down.l3) {}

    if (Ps3.event.button_up.l3) {
        if (pressed.ps)
            set_transpose(left_bumper_fine_transpose);
        else
            set_transpose(left_bumper_coarse_transpose);
    }


    if (Ps3.event.button_down.r3) {}

    if (Ps3.event.button_up.r3) {
        if (pressed.ps)
            set_transpose(right_bumper_fine_transpose);
        else
            set_transpose(right_bumper_coarse_transpose);
    }


/* Digital select, start, & ps button events */
    if (Ps3.event.button_down.select)
        if (pressed.ps) {
            toggle_aftertouch_mode();
        } else if (pressed.start) {
            initialize_notes();
        } else { 
            pressed.select = true;
        }

    if (Ps3.event.button_up.select)
        pressed.select = false;


    if (Ps3.event.button_down.start) {
        if (pressed.ps) {
            midi_stop_all_notes();
        } else if (pressed.select) {
            initialize_notes();
        } else {  
            pressed.start = true; 
        }
    }

    if (Ps3.event.button_up.start)
        pressed.start = false;


    if (Ps3.event.button_down.ps)
        pressed.ps = true;

    if (Ps3.event.button_up.ps)
        pressed.ps = false;


/* Analog stick value events */
    if (abs(Ps3.event.analog_changed.stick.lx) > 1) 
        midi_sendCC(left_joystick_x_cc, Ps3.data.analog.stick.lx, false);

    if (abs(Ps3.event.analog_changed.stick.ly) > 1)
        midi_sendCC(left_joystick_y_cc, Ps3.data.analog.stick.ly, true);


    if (abs(Ps3.event.analog_changed.stick.rx) > 1) 
        midi_sendCC(right_joystick_x_cc, Ps3.data.analog.stick.rx, false);

    if (abs(Ps3.event.analog_changed.stick.ry) > 1)
        midi_sendCC(right_joystick_y_cc, Ps3.data.analog.stick.ry, true);


/* Analog D-pad button events */
    if (abs(Ps3.event.analog_changed.button.up)) 
        midi_sendAftertouch(NOTE_BUTTON::UP, Ps3.data.analog.button.up, aftertouch_mode);


    if (abs(Ps3.event.analog_changed.button.right)) 
        midi_sendAftertouch(NOTE_BUTTON::RIGHT, Ps3.data.analog.button.right, aftertouch_mode);

    
    if (abs(Ps3.event.analog_changed.button.down))
        midi_sendAftertouch(NOTE_BUTTON::DOWN, Ps3.data.analog.button.down, aftertouch_mode);

    
    if (abs(Ps3.event.analog_changed.button.left))
        midi_sendAftertouch(NOTE_BUTTON::LEFT, Ps3.data.analog.button.left, aftertouch_mode);


/* Analog shape button events */
    if (abs(Ps3.event.analog_changed.button.triangle))
        midi_sendAftertouch(NOTE_BUTTON::TRIANGLE, Ps3.data.analog.button.triangle, aftertouch_mode);


    if (abs(Ps3.event.analog_changed.button.circle))
        midi_sendAftertouch(NOTE_BUTTON::CIRCLE, Ps3.data.analog.button.circle, aftertouch_mode);

    
    if (abs(Ps3.event.analog_changed.button.cross))
        midi_sendAftertouch(NOTE_BUTTON::CROSS, Ps3.data.analog.button.cross, aftertouch_mode);

    
    if (abs(Ps3.event.analog_changed.button.square))
        midi_sendAftertouch(NOTE_BUTTON::SQUARE, Ps3.data.analog.button.square, aftertouch_mode);
        

/* Analog shoulder & trigger button events */
    if (abs(Ps3.event.analog_changed.button.l1)) {
        set_velocity(Ps3.data.analog.button.l1);
    }  
    
    if (abs(Ps3.event.analog_changed.button.r1)) {}


    if (abs(Ps3.event.analog_changed.button.l2) || abs(Ps3.event.analog_changed.button.r2))
        midi_sendPitchBend(Ps3.data.analog.button.r2, Ps3.data.analog.button.l2);
    
    
/* Battery events */
    if (battery != Ps3.data.status.battery) {
        battery = Ps3.data.status.battery;
        // Serial.print("The controller battery is ");
        // if (battery == ps3_status_battery_charging)      Serial.println("charging");
        // else if (battery == ps3_status_battery_full)     Serial.println("FULL");
        // else if (battery == ps3_status_battery_high)     Serial.println("HIGH");
        // else if (battery == ps3_status_battery_low)      Serial.println("LOW");
        // else if (battery == ps3_status_battery_dying)    Serial.println("DYING");
        // else if (battery == ps3_status_battery_shutdown) Serial.println("SHUTDOWN");
        // else Serial.println("UNDEFINED");
    }
}


// static void set_LEDs(int channel) {
//     ps3_cmd_t *cmd;
//     switch (channel) {
//     case 16:
//         cmd->led1 = 0;
//         cmd->led2 = 0;
//         cmd->led3 = 0;
//         cmd->led4 = 0;
//         break;

//     case 15:
//         cmd->led1 = 1;
//         cmd->led2 = 1;
//         cmd->led3 = 1;
//         cmd->led4 = 1;
//         break;

//     case 14:
//         cmd->led1 = 0;
//         cmd->led2 = 1;
//         cmd->led3 = 1;
//         cmd->led4 = 1;
//         break;

//     case 13:
//         cmd->led1 = 1;
//         cmd->led2 = 0;
//         cmd->led3 = 1;
//         cmd->led4 = 1;
//         break;

//     case 12:
//         cmd->led1 = 0;
//         cmd->led2 = 0;
//         cmd->led3 = 1;
//         cmd->led4 = 1;
//         break;

//     case 11:
//         cmd->led1 = 1;
//         cmd->led2 = 1;
//         cmd->led3 = 0;
//         cmd->led4 = 1;
//         break;

//     case 10:

//         cmd->led1 = 0;
//         cmd->led2 = 1;
//         cmd->led3 = 0;
//         cmd->led4 = 1;
//         break;

//     case 9:
//         cmd->led1 = 1;
//         cmd->led2 = 0;
//         cmd->led3 = 0;
//         cmd->led4 = 1;
//         break;

//     case 8:
//         cmd->led1 = 0;
//         cmd->led2 = 0;
//         cmd->led3 = 0;
//         cmd->led4 = 1;
//         break;

//     case 7:
//         cmd->led1 = 1;
//         cmd->led2 = 1;
//         cmd->led3 = 1;
//         cmd->led4 = 0;
//         break;
        
//     case 6:
//         cmd->led1 = 0;
//         cmd->led2 = 1;
//         cmd->led3 = 1;
//         cmd->led4 = 0;
//         break;

//     case 5:
//         cmd->led1 = 1;
//         cmd->led2 = 0;
//         cmd->led3 = 1;
//         cmd->led4 = 0;
//         break;

//     case 4:
//         cmd->led1 = 0;
//         cmd->led2 = 0;
//         cmd->led3 = 1;
//         cmd->led4 = 0;
//         break;

//     case 3:
//         cmd->led1 = 1;
//         cmd->led2 = 1;
//         cmd->led3 = 0;
//         cmd->led4 = 0;
//         break;

//     case 2:
//         cmd->led1 = 0;
//         cmd->led2 = 1;
//         cmd->led3 = 0;
//         cmd->led4 = 0;
//         break;

//     case 1:
//         cmd->led1 = 1;
//         cmd->led2 = 0;
//         cmd->led3 = 0;
//         cmd->led4 = 0;
//         break;

//     default:
//         cmd->led1 = 0;
//         cmd->led2 = 0;
//         cmd->led3 = 0;
//         cmd->led4 = 0;
//         break;
//     }
// }


static void set_player() {
    player = midi_get_active_channel();
    // Serial.print("Setting LEDs to player "); Serial.println(player, DEC);       
    Ps3.setPlayer(player); 
}


void onConnect() {
    // Serial.println("Connected.");
    Ps3.setPlayer(1);
    // set_LEDs(midi_get_active_channel());
}


void ps3_setup() {
    Ps3.attach(ps3_midi_translate);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin(CURRENT_MASTER_MAC);
}

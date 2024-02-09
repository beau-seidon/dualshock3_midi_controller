# Dualshock3-MIDI-Controller
ESP32 firmware to convert Dualshock3 bluetooth input to MIDI commands

-----------

> <diagram_placeholder/>


* The D-Pad and Shape buttons play notes when pressed, and are pressure-sensitive so they also send Aftertouch data.

* L1 pressure sensor acts as a Note Velocity damper; the unpressed default is full volume, and newly played notes will be quieter as L1 is pressed harder.

* R1 acts like a sustain pedal; it sends a momentary MIDI CC64 to hold played notes until R1 is released.

* The L2 and R2 triggers send pitch bend data.

* The joysticks send data on 4 CC voices, one for each axis of each joystick. The CC numbers are Lx:20, Ly:21, Rx:22, Ry:23.

* Pressing the joysticks in will transpose the set of notes that the other buttons play. L3 transposes down 1 octove, and R3 transposes up 1 octave. Transpose is disabled while any note buttons are pressed, to avoid stuck notes.
 
 
* The PS button is used as a modifer for other buttons to call secondary functions.

* With PS held, the D-Pad and Shape buttons will change the button map to different notes corresponding to the selected diatonic scale.

* With PS held, pressing L1 or R1 will decrease or increase the MIDI channel.

* With PS held, pressing L3 or R3 will transpose the note button map down or up by 1 semitone.


* Aftertouch is toggleable between Key and Channel by pressing Select with PS held. (Will add the option to disable aftertouch soon)

* Pressing Start with PS held will send a NoteOff message for every note on the active channel, in case any get stuck for some reason.

* Pressing Start and Select at the same time will reset transpose to default, and turn all notes off.



To connect the PS3 controller to the ESP32, first determine the MAC address associated with the controller by plugging it in to a PC with a mini-USB cable, and using Sixaxis Pair Tool. 

Type this MAC address into the Config.h file before compiling so the controller will think the ESP32 is the "master" (the PS3 it is supposed to be paired with).  
Alternatively, use the Sixasis Pair Tool to reassociate the controller with the default MAC already typed into config.h (note: this will unpair it from the PS3 it was associated with).

To receive MIDI via USB serial, I connect the ESP32 to my PC (no other wires are needed), and use the Hairless Serial-MIDI bridge software, then send it through the loopMIDI virtual input port into my DAW.  
You can also output MIDI signals from the ESP32 built-in UART, using a DIN or TRS connector via a standard MIDI output buffer circuit, instead of USB into middleware. This would let you plug directly into synths or other hardware. 



## References:

https://dronebotworkshop.com/ps3-esp32/


### Software

https://www.filehorse.com/download-sixaxispairtool/

https://projectgus.github.io/hairless-midiserial/

https://www.tobias-erichsen.de/software/loopmidi.html


### Code Libraries

https://github.com/jvpernis/esp32-ps3

https://github.com/FortySevenEffects/arduino_midi_library


### MIDI Spec

https://www.midi.org/specifications-old/item/midi-din-electrical-specification

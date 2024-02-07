#include <Arduino.h>
#include <ps3_handler.h>
#include <midi_handler.h>
#include <note_handler.h>



void setup()
{
    // pinMode(LED_BUILTIN, OUTPUT);
    // Serial.begin(115200);

    ps3_setup();
    midi_setup();
    initialize_notes();
}



void loop()
{
    if(!Ps3.isConnected()) return;
    delay(2000);
}

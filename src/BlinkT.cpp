/*
#include <Arduino.h>

static const unsigned int LED = 13;

void setup() {
    // put your setup code here, to run once:
    pinMode(LED, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(LED, HIGH);
    usbMIDI.sendNoteOn(60, 100, 1);
    delay(1500);
    digitalWrite(LED, LOW);
    usbMIDI.sendNoteOff(60, 100, 1);
    delay(1500);
}
*/
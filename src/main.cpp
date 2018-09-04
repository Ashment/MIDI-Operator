#include "MultiplexInput.h"

static const unsigned int LED = 13;

InputMatrix inpMat = InputMatrix();

void setup() {
    // put your setup code here, to run once:
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
    inpMat.updateMatrix();
    inpMat.GenerateMidiNotes();
    delay(20);
}
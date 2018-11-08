#include <Arduino.h>

const static byte sPotPin = 0;

const static byte sizeX = 3;
const static byte sizeY = 3;

const byte RowPins[sizeY] = {6,7,8};
const byte ColPins[sizeX] = {16,17,18};

const byte NoteMatrix[sizeX][sizeY] = {
    {57, 59, 60},
    {62, 64, 65},
    {67, 69, 71}
};

enum KeyState{
    Idle,
    KeyDown,
    KeyUp,
    Depressed,
};

class InputMatrix{
public:
    byte KeyStats[sizeX][sizeY];
    KeyState deltaStates[sizeX][sizeY];


    //CONSTRUCTOR
    InputMatrix(){
        for(byte i : RowPins){
            pinMode(i, INPUT_PULLUP);
        }
        for(byte i : ColPins){
            pinMode(i, OUTPUT);
        }
    }

    //METHODS
    void updateMatrix(){
        for(int xx = 0; xx < sizeX; xx++){
            //Iterate through columns, pulling cur iterating pin low
            pinMode(ColPins[xx], OUTPUT);
            digitalWrite(ColPins[xx], LOW);

            for(int yy = 0; yy < sizeY; yy++){
                pinMode(RowPins[yy], INPUT_PULLUP);
                KeyState newDeltaState;
                byte newKeyState = digitalRead(RowPins[yy]);

                if(KeyStats[xx][yy] == LOW){
                    switch(newKeyState){
                        case HIGH:
                            newDeltaState = KeyState(KeyUp);
                            break;
                        case LOW:
                            newDeltaState = KeyState(Depressed);
                            break;
                    }
                }
                else if(KeyStats[xx][yy] == HIGH){
                    switch(newKeyState){
                        case HIGH:
                            newDeltaState = KeyState(Idle);
                            break;
                        case LOW:
                            newDeltaState = KeyState(KeyDown);
                            break;
                    }
                }

                deltaStates[xx][yy] = newDeltaState;
                KeyStats[xx][yy] = newKeyState;
            }
            digitalWrite(ColPins[xx], HIGH);
        }
    }


    void GenerateMidiNotes(){
        //Iterates through key statuses and generates MIDI on/off data
        for(int xx = 0; xx < sizeX; xx++){
            for(int yy = 0; yy < sizeY; yy++){
                KeyState cur = deltaStates[xx][yy];
                if (cur == KeyState(KeyDown)){
                    usbMIDI.sendNoteOn(NoteMatrix[xx][yy], 80, 1);
                }else if(cur == KeyState(KeyUp)){
                    usbMIDI.sendNoteOff(NoteMatrix[xx][yy], 80, 1);
                }
            }
        }
    }

};
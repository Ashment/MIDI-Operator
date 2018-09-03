#include <Arduino.h>

const static byte sizeX = 3;
const static byte sizeY = 3;

const byte RowPins[sizeY] = {6,7,8};
const byte ColPins[sizeX] = {16,17,18};

class InputMatrix{
public:
    byte KeyStats[sizeX][sizeY];

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
            //Iterate through columns, driving current iterating pin low
            pinMode(ColPins[xx], OUTPUT);
            digitalWrite(ColPins[xx], LOW);

            for(int yy = 0; yy < sizeY; yy++){
                pinMode(RowPins[yy], INPUT_PULLUP);
                KeyStats[xx][yy] = digitalRead(RowPins[yy]);
                if(KeyStats[xx][yy] == LOW){
                    Serial.print("Key Detected: ");
                    Serial.print(xx); Serial.print(", ");
                    Serial.print(yy); Serial.println("\n");
                }
            }
            digitalWrite(ColPins[xx], HIGH);
        }
    }



private:
    void InitializePins();

};
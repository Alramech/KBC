#include "PS2Keyboard.h"
#include "UnoJoy.h"

const int DataPin = 4;
const int IRQpin =  3;


int Triangle = 4;
int Square = 5;
int Cross = 3;
int Circle = 2;

int R1 = 6;
int R2 = 7;
int L1 = 0;
int L2 = 1;

int Left = 8;
int Up = 9;
int Right = 10;
int Down = 11;

int Start =  12;

int held[13] = { };

PS2Keyboard keyboard;

void setup() {
  delay(500);
  keyboard.begin(DataPin, IRQpin);
  //Serial.begin(9600);
  //Serial.println("Keyboard Test:");
  setupUnoJoy();
  pinMode(13, OUTPUT);
}

void loop() {
  if (keyboard.available()) {
    
    // read the next key
    uint16_t r = 0;
    uint16_t c;// = keyboard.read();
    
    while (1) {
      while (not keyboard.available()) {
        
      }
      c = keyboard.read();
      if (c == 0) {
        r == c;
        break;
      }
      if (c == 0xF0) {
        r |= 0x100;
        //Serial.println(r);
        //Serial.print("f0\n");
      } else if (c == 0xE0) {
        r |= 0x200;
        //Serial.println(r);
        //Serial.print("e0\n");
      } else {
        r += c&0xFF;
        //Serial.println(r);
        //Serial.println(c);
        //Serial.print("rf\n");
        break;
      }
    }
    
    // check for some of the special keys
    if (r == 0x4D) {
      held[Start] = 1;
    } else if (r == 0x14D) {
      held[Start] = 0;
    } else if (r == 0x1B) {
      held[Square] = 1;
    } else if (r == 0x11B) {
      held[Square] = 0;
    } else if (r == 0x1C) {
      held[Circle] = 1;
    } else if (r == 0x11C) {
     held[Circle] = 0;
    } else if (r == 0x23) {
      held[Triangle] = 1;
    } else if (r == 0x123) {
      held[Triangle] = 0;
    } else if (r == 0x2B) {
      held[Cross] = 1;
    } else if (r == 0x12B) {
      held[Cross] = 0;
    } else if (r == 0x1D) {
      held[R1] = 1;
    } else if (r == 0x11D) {
      held[R1] = 0;
    } else if (r == 0x24) {
      held[R2] = 1;
    } else if (r == 0x124) {
      held[R2] = 0;
    } else if (r == 0x2D) {
      held[L1] = 1;
    } else if (r == 0x12D) {
      held[L1] = 0;
    } else if (r == 0x34) {
      held[L2] = 1;
    } else if (r == 0x134) {
      held[L2] = 0;
    } else if (r == 0x275) {
      held[Up] = 1;
    } else if (r == 0x375) {
      held[Up] = 0;
    } else if (r == 0x272) {
      held[Down] = 1;
    } else if (r == 0x372) {
      held[Down] = 0;
    } else if (r == 0x26B) {
      held[Left] = 1;
    } else if (r == 0x36B) {
      held[Left] = 0;
    } else if (r == 0x274) {
      held[Right] = 1;
    } else if (r == 0x374) {
      held[Right] = 0;
    }
    dataForController_t controllerData = getControllerData(c);
    setControllerData(controllerData); 
    for (int i = 0; i < 13; i++){
       //Serial.print(held[i]);
    }
    //Serial.print("\n");
  }
  //Serial.print(digitalRead(IRQpin));
}

dataForController_t getControllerData(char c){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  controllerData.triangleOn = held[Triangle];
  controllerData.circleOn = held[Circle];
  controllerData.squareOn = held[Square];
  controllerData.crossOn = held[Cross];
  controllerData.dpadLeftOn = held[Left];
  controllerData.dpadRightOn = held[Right];
  controllerData.dpadUpOn = held[Up];
  controllerData.dpadDownOn = held[Down];

  controllerData.r1On = held[R1];
  controllerData.r2On = held[R2];
  controllerData.l1On = held[L1];
  controllerData.l2On = held[L2];


  
  controllerData.startOn = held[Start];
  
  // And return the data!
  return controllerData;
}

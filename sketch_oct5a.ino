 #include <Arduino.h>


void updateEncoder();


#include <HID-Project.h>

#include "keybinds.h"


#define CLK 2

#define DT 3

#define SW 4


volatile uint8_t encoderState = 0;


// Track button states

bool lastKeyState[10] = {false};


// Debounce timing

unsigned long lastDebounceTime[10] = {0};

const unsigned long KEY_DEBOUNCE = 30;


// Encoder Direction Safety Lock Variables

#define DIR_NONE 0

#define DIR_CW   1

#define DIR_CCW  2


volatile uint8_t lastDirection = DIR_NONE;

volatile unsigned long lastEncoderTurnTime = 0;

const unsigned long DIRECTION_COOLDOWN = 150; // Milliseconds to block opposite direction changes


void setup() {  

  BootKeyboard.begin();

  Consumer.begin();

 

  pinMode(A1, INPUT_PULLUP);

  pinMode(A2, INPUT_PULLUP);

 

  pinMode(5, OUTPUT);

  pinMode(6, OUTPUT);

  pinMode(7, OUTPUT);

  pinMode(8, OUTPUT);

  pinMode(9, OUTPUT);


  digitalWrite(5, HIGH);

  digitalWrite(6, HIGH);

  digitalWrite(7, HIGH);

  digitalWrite(8, HIGH);

  digitalWrite(9, HIGH);


  pinMode(CLK, INPUT_PULLUP);

  pinMode(DT, INPUT_PULLUP);

  pinMode(SW, INPUT_PULLUP);


  encoderState = (digitalRead(CLK) << 1) | digitalRead(DT);

 

  attachInterrupt(digitalPinToInterrupt(CLK), updateEncoder, CHANGE);

  attachInterrupt(digitalPinToInterrupt(DT), updateEncoder, CHANGE);

}


void checkKey(int keyNum, int pinRead, void (*keyFunction)()) {

  bool isPressed = (pinRead == LOW);

  unsigned long now = millis();


  if (isPressed != lastKeyState[keyNum]) {

    if (now - lastDebounceTime[keyNum] > KEY_DEBOUNCE) {

      lastKeyState[keyNum] = isPressed;

      lastDebounceTime[keyNum] = now;

     

      if (isPressed) {

        keyFunction();

      }

    }

  }

}


void loop() {

  // Encoder Button (Play/Pause)

  checkKey(0, digitalRead(SW), onEncoderButton);


  // Row 1

  digitalWrite(5, LOW);

  checkKey(9, digitalRead(A1), onKey9);

  digitalWrite(5, HIGH);


  // Row 2

  digitalWrite(6, LOW);

  checkKey(8, digitalRead(A1), onKey8);

  checkKey(4, digitalRead(A2), onKey4);

  digitalWrite(6, HIGH);


  // Row 3

  digitalWrite(7, LOW);

  checkKey(7, digitalRead(A1), onKey7);

  checkKey(3, digitalRead(A2), onKey3);

  digitalWrite(7, HIGH);


  // Row 4

  digitalWrite(8, LOW);

  checkKey(6, digitalRead(A1), onKey6);

  checkKey(2, digitalRead(A2), onKey2);

  digitalWrite(8, HIGH);


  // Row 5

  digitalWrite(9, LOW);

  checkKey(5, digitalRead(A1), onKey5);

  checkKey(1, digitalRead(A2), onKey1);

  digitalWrite(9, HIGH);

}


void updateEncoder() {  

  uint8_t pinState = (digitalRead(CLK) << 1) | digitalRead(DT);

  uint8_t transition = (encoderState << 2) | pinState;

  unsigned long now = millis();


  switch (transition) {

    case 0b0001: case 0b0111: case 0b1110: case 0b1000:

      if (pinState == 0b11) {

        // Block CCW if CW was registered recently

        if (lastDirection == DIR_CCW && (now - lastEncoderTurnTime < DIRECTION_COOLDOWN)) {

          break;

        }

        lastDirection = DIR_CW;

        lastEncoderTurnTime = now;

        onEncoderCW();

      }

      break;


    case 0b0010: case 0b1011: case 0b1101: case 0b0100:

      if (pinState == 0b11) {

        // Block CW if CCW was registered recently

        if (lastDirection == DIR_CW && (now - lastEncoderTurnTime < DIRECTION_COOLDOWN)) {

          break;

        }

        lastDirection = DIR_CCW;

        lastEncoderTurnTime = now;

        onEncoderCCW();

      }

      break;


    default:

      break;

  }


  encoderState = pinState;

}


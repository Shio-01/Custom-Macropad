 #ifndef KEYBINDS_H

#define KEYBINDS_H


#include <Arduino.h>

#include <HID-Project.h>


// ==========================================

//           MODIFIER ALIASES

// ==========================================

#define MOD_NONE   0

#define MOD_CTRL   KEY_LEFT_CTRL

#define MOD_ALT    KEY_LEFT_ALT

#define MOD_SHIFT  KEY_LEFT_SHIFT

#define MOD_WIN    KEY_LEFT_GUI


// ==========================================

//    RAW USB HID KEYCODES FOR F13 - F24

// (Prevents HID-Project ASCII translation)

// ==========================================

#define RAW_F13 0x68

#define RAW_F14 0x69

#define RAW_F15 0x6A

#define RAW_F16 0x6B

#define RAW_F17 0x6C

#define RAW_F18 0x6D

#define RAW_F19 0x6E

#define RAW_F20 0x6F

#define RAW_F21 0x70

#define RAW_F22 0x71

#define RAW_F23 0x72

#define RAW_F24 0x73


// ==========================================

//            KEY MAPPING

// ==========================================


// Key 1: F13

#define KEY1_MOD1 MOD_NONE

#define KEY1_MOD2 MOD_NONE

#define KEY1_KEY  RAW_F13


// Key 2: F14

#define KEY2_MOD1 MOD_NONE

#define KEY2_MOD2 MOD_NONE

#define KEY2_KEY  RAW_F14


// Key 3: F15

#define KEY3_MOD1 MOD_NONE

#define KEY3_MOD2 MOD_NONE

#define KEY3_KEY  RAW_F15


// Key 4: F16

#define KEY4_MOD1 MOD_NONE

#define KEY4_MOD2 MOD_NONE

#define KEY4_KEY  RAW_F16


// Key 5: F17

#define KEY5_MOD1 MOD_NONE

#define KEY5_MOD2 MOD_NONE

#define KEY5_KEY  RAW_F17


// Key 6: F18

#define KEY6_MOD1 MOD_NONE

#define KEY6_MOD2 MOD_NONE

#define KEY6_KEY  RAW_F18


// Key 7: F19

#define KEY7_MOD1 MOD_NONE

#define KEY7_MOD2 MOD_NONE

#define KEY7_KEY  RAW_F19


// Key 8: F20

#define KEY8_MOD1 MOD_NONE

#define KEY8_MOD2 MOD_NONE

#define KEY8_KEY  RAW_F20


// Key 9: F21

#define KEY9_MOD1 MOD_NONE

#define KEY9_MOD2 MOD_NONE

#define KEY9_KEY  RAW_F21



// ==========================================

//          EXECUTION FUNCTIONS

// ==========================================


inline void sendShortcut(uint8_t m1, uint8_t m2, uint16_t key) {

  // 1. Handle Consumer / Media keys

  if (key >= MEDIA_FAST_FORWARD && key <= MEDIA_VOLUME_MUTE) {

    Consumer.write(ConsumerKeycode(key));

    return;

  }


  // 2. Press Modifiers

  if (m1 != MOD_NONE) BootKeyboard.press(KeyboardKeycode(m1));

  if (m2 != MOD_NONE) BootKeyboard.press(KeyboardKeycode(m2));


  // 3. Handle Key Presses using explicit KeyboardKeycode type cast

  if (key != 0) {

    BootKeyboard.press(KeyboardKeycode(key));

  }

 

  delay(30);

  BootKeyboard.releaseAll();

}


// Rotary Encoder Triggers

inline void onEncoderButton() { Consumer.write(MEDIA_PLAY_PAUSE); }

inline void onEncoderCW()     { Consumer.write(MEDIA_VOLUME_DOWN); }

inline void onEncoderCCW()    { Consumer.write(MEDIA_VOLUME_UP); }


// Key Matrix Triggers

inline void onKey1() { sendShortcut(KEY1_MOD1, KEY1_MOD2, KEY1_KEY); }

inline void onKey2() { sendShortcut(KEY2_MOD1, KEY2_MOD2, KEY2_KEY); }

inline void onKey3() { sendShortcut(KEY3_MOD1, KEY3_MOD2, KEY3_KEY); }

inline void onKey4() { sendShortcut(KEY4_MOD1, KEY4_MOD2, KEY4_KEY); }

inline void onKey5() { sendShortcut(KEY5_MOD1, KEY5_MOD2, KEY5_KEY); }

inline void onKey6() { sendShortcut(KEY6_MOD1, KEY6_MOD2, KEY6_KEY); }

inline void onKey7() { sendShortcut(KEY7_MOD1, KEY7_MOD2, KEY7_KEY); }

inline void onKey8() { sendShortcut(KEY8_MOD1, KEY8_MOD2, KEY8_KEY); }

inline void onKey9() { sendShortcut(KEY9_MOD1, KEY9_MOD2, KEY9_KEY); }


#endif 
#ifndef Pins_H
#define Pins_H

#include "Esp.h"

typedef struct Pins
{
    Pins();
      uint8_t OnBoardLED;

      uint8_t OpenButton;
      uint8_t CloseButton;
      uint8_t DebugButton;

      uint8_t IR_Pin;

      int MotorPin_1;
      int MotorPin_2;
      int MotorPin_3;
      int MotorPin_4;

} Pins;

extern Pins pins;

#endif

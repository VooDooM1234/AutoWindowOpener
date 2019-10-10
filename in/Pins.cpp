#include "Pins.h"
#include "Esp.h"

Pins::Pins()
{
/*
*   Don't use pin D4 - ESP flash pin.
*/

    OnBoardLED = 2;

    OpenButton = D2;  //15 - d8
    CloseButton = D1; //13 - d7
    DebugButton = D0; //12 - d6

   // IR_Pin = D5;

    MotorPin_1 = D5;
    MotorPin_2 = D6;
    MotorPin_3 = D7;
    MotorPin_4 = D8;
}

Pins pins;

#include "Pins.h"
#include "Esp.h"

Pins::Pins()
{

    OnBoardLED = 2;

    OpenButton = D8;  //15 - d8
    CloseButton = D7; //13 - d7
    DebugButton = D6; //12 - d6

    IR_Pin = D5;

    MotorPin_1 = D0;
    MotorPin_2 = D1;
    MotorPin_3 = D2;
    MotorPin_4 = D3;
}

Pins pins;

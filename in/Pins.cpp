#include "Pins.h"
#include "Esp.h"

Pins::Pins()
{
    /*
*   Don't use pin D4 - ESP flash pin.

        D0 = GPIO16;
        D1 = GPIO5;
        D2 = GPIO4;
        D3 = GPIO0;
        D4 = GPIO2;
        D5 = GPIO14;
        D6 = GPIO12;
        D7 = GPIO13;
        D8 = GPIO15;
        D9 = GPIO3;
        D10 = GPIO1;
        LED_BUILTIN = GPIO16 (auxiliary constant for the board LED, not a board pin);
        */

    OnBoardLED = 2;

    OpenButton = D0;  //15 - d8
    CloseButton = D1; //13 - d7
    DebugButton = D2; //12 - d6

    // IR_Pin = D5;

    MotorPin_1 = D5;
    MotorPin_2 = D6;
    MotorPin_3 = D7;
    MotorPin_4 = D8;
}

Pins pins;

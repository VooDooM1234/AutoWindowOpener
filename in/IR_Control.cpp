
#include "Esp.h"
#include "IR_Control.h"
#include "StepperControl.h"

#include <IRrecv.h>
#include <IRutils.h>
#include <IRremoteESP8266.h>

IRrecv irrecv(D5, 1024, 50, true);
decode_results results;

bool remoteState;
unsigned long remoteButtonDownMs;

//IR_Control::IR_Control(String name, int attachTo);

void IR_Control::IRSetup()
{
    irrecv.enableIRIn(pin);
}

int IR_Control::IR_Run()
{
    String data = resultToHexidecimal(&results);
    uint8_t remoteButton;
    uint8_t holdCount = 0;

    // if (data != "FFFFFFFFFFFFFFFF")
    //{
    Serial.print("Data Recieved: ");
    Serial.println(data);
    //OPEN
    if (data == "2FDD827")
    {
        remoteButton = 0;
        Serial.println("Remote Opening");
    }
    //CLOSE
    else if (data == "2FDF807")
    {
        remoteButton = 1;
        Serial.println("Remote Closing");
    }
    //returned when remote is being held
    else if (data == "FFFFFFFFFFFFFFFF")
    {
        Serial.println("Holding");
    }

    return remoteButton;
    // }
}

bool IR_Control::IRHasRecievedData()
{
    int prevState = remoteState;
    remoteState = irrecv.decode(&results);
//doesnot work - no idea what decode actyually returns

    if (prevState == LOW && remoteState == HIGH)
    {
        remoteButtonDownMs = millis();
        return true;
    }

    else if (prevState == HIGH && remoteState == HIGH)
    {
        if (millis() - remoteButtonDownMs < 50)
        {
            // ignore this for debounce
            return false;
        }
        return false;
    }
}

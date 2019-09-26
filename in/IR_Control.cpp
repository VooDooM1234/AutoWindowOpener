
#include "Esp.h"
#include "IR_Control.h"
#include "StepperControl.h"

#include <IRrecv.h>
#include <IRremoteESP8266.h>

const uint8_t kTimeout = 15;
const uint16_t kCaptureBufferSize = 1024;

IRrecv irrecv(D5, kCaptureBufferSize, kTimeout, true);
decode_results results;

//IR_Control::IR_Control(String name, int attachTo);

void IR_Control::IRSetup()
{
    irrecv.enableIRIn(pin);
}

int IR_Control::IR_Run()
{
    String data = resultToHexidecimal(&results);
    uint8_t remoteButton = null;

   // if (data != "FFFFFFFFFFFFFFFF")
    //{
        Serial.print("Data Recieved: ");
        Serial.println(data);

        if (data == "2FDD827")
        {
            remoteButton = 0;
            Serial.println("Remote Opening");
        }
        else if (data == "2FDF807")
        {
            remoteButton = 1;
            Serial.println("Remote Closing");
        }

        return remoteButton;
   // }
}

bool IR_Control::IRHasRecievedData()
{

    if (irrecv.decode(&results))
    {
        // Serial.println("IR Data Recieved");
        return true;
    }

    return false;
}

#include <Stepper.h>

#include "Esp.h"
#include "StepperControl.h"
#include "Pins.h"

//32 steps per rev * gear ratio of 64:1 = 2038
const int stepsPerRevolution = 2038;
//speed in RPM
const int speed = 60;
//8 revolutions to open/close window
const int windowRevolutions = 8;

String windowState = "";

Pins motorPins;
Stepper myStepper(stepsPerRevolution, motorPins.MotorPin_1, motorPins.MotorPin_2, motorPins.MotorPin_3, motorPins.MotorPin_4);

void StepperControl::StepperSetup()
{
  myStepper.setSpeed(speed);
}

void StepperControl::StepperRun(byte direction)
{
  //0 for open 1 for close
  if (direction == 0)
  {
    if (windowState != "open")
    {
      // step one revolution in one direction:
      Serial.println("~~~~~OPENING~~~~~");
      myStepper.step(stepsPerRevolution);
      windowState = "open";
      delay(10);
    }
    else
    {
      Serial.println("Already Open");
    }
  }
  else if (direction == 1)
  {
if (windowState != "closed")
    {
      // step one revolution in one direction:
      Serial.println("~~~~~CLOSING~~~~~");
      myStepper.step(stepsPerRevolution);
      windowState = "closed";
      delay(10);
    }
    else
    {
      Serial.println("Already Closed");
    }
  }
}

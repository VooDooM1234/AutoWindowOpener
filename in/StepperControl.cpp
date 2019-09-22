#include <Stepper.h>

#include "Esp.h"
#include "StepperControl.h"

//32 steps per rev * gear ratio of 64:1 = 2038
const int stepsPerRevolution = 2038; 
//speed in RPM
const int speed = 60;               

// const int OpeningSteps = 
// const int ClosingSteps = 


StepperControl::StepperControl();

Stepper myStepper(stepsPerRevolution, D0, D1, D2, D3);

void StepperControl::StepperSetup()
{
  myStepper.setSpeed(speed);
}

void StepperControl::StepperRun(byte direction)
{
  //0 for open 1 for close
  if (direction == 0)
  {
    // step one revolution  in one direction:
    Serial.println("~~~~~OPENING~~~~~");
    myStepper.step(stepsPerRevolution);
    delay(10);
  }
  else if (direction == 1)
  {
    // step one revolution in the other direction:
    Serial.println("~~~~~CLOSING~~~~~");
    myStepper.step(stepsPerRevolution);
    delay(10);
  }
}

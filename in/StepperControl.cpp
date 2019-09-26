#include <Stepper.h>

#include "Esp.h"
#include "StepperControl.h"

//32 steps per rev * gear ratio of 64:1 = 2038
const int stepsPerRevolution = 2038;
//speed in RPM
const int speed = 60;

// const int OpeningSteps =
// const int ClosingSteps =

const int MotorPin_1 = D0;
const int MotorPin_2 = D1;
const int MotorPin_3 = D2;
const int MotorPin_4 = D3;

//StepperControl::StepperControl();

Stepper myStepper(stepsPerRevolution, MotorPin_1, MotorPin_2, MotorPin_3, MotorPin_4);

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

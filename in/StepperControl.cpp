/*

  

*/
#include "Esp.h"
#include "StepperControl.h"
#include "Pins.h"

Pins motorPins;

void StepperControl::StepperSetup()
{
  pinMode(motorPins.MotorPin_1, OUTPUT);
  pinMode(motorPins.MotorPin_2, OUTPUT);
  pinMode(motorPins.MotorPin_3, OUTPUT);
  pinMode(motorPins.MotorPin_4, OUTPUT);
}

void StepperControl::writeStep(int outArray[4])
{
  digitalWrite(motorPins.MotorPin_1, outArray[0]);
  digitalWrite(motorPins.MotorPin_2, outArray[1]);
  digitalWrite(motorPins.MotorPin_3, outArray[2]);
  digitalWrite(motorPins.MotorPin_4, outArray[3]);
}

bool StepperControl::currentStateChecker(bool direction)
{

  if (windowState != "open" && direction == true)
  {
    Serial.println("~~~~~OPENING~~~~~");
    Serial.println("Wait...!");
    windowState = "open";
    return true;
  }
  else if (windowState == "open" && direction == true)
  {
    Serial.println("Already Open");
    return false;
  }

  else if (windowState != "closed" && direction == false)
  {

    Serial.println("~~~~~CLOSING~~~~~");
    Serial.println("Wait...!");
    windowState = "closed";
    return true;
  }
  else
  {
    Serial.println("Already Closed");
    return false;
  }
}

void StepperControl::stepper(bool direction)
{
  if ((Step >= 0) && (Step < 8))
  {
    //begin stepping
    writeStep(stepsMatrix[Step]);
  }
  else
  {
    writeStep(arrayDefault);
  }
  //set direction of stepping based on pased direction val
  (direction == true) ? (Step++) : (Step--);

  if (Step > 7)
  {
    Step = 0;
  }
  else if (Step < 0)
  {
    Step = 7;
  }
}

void StepperControl::StepperRun(bool direction)
{

  unsigned long currentMicros;
  int stepsLeft = (stepsPerRevolution * windowRevolutions);

  motorTime = 0;
  lastTime = micros();

  // if current state and direction check passes
  if (currentStateChecker(direction) == true)
  {

    while (stepsLeft > 0)
    {
      currentMicros = micros();

      if (currentMicros - lastTime >= speed)
      {

        stepper(direction);
        motorTime += micros() - lastTime;
        lastTime = micros();
        stepsLeft--;
      }
      delay(1);
    }

    Serial.println(motorTime);

    //delay(2000);

    Serial.println("Complete!");
    stepsLeft = stepsPerRevolution;
  }
  else
  {
    Serial.println("Error");
  }
}

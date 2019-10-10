#include <Stepper.h>

#include "Esp.h"
#include "StepperControl.h"
#include "Pins.h"

#define IN1 14 //GPIO 14
#define IN2 12 //GPIO 12
#define IN3 13 //GPIO 13
#define IN4 15 //GPIO 15

//32 steps per rev * gear ratio of 64:1 = 2038
const int stepsPerRevolution = 2038;
//speed in RPM
const int speed = 60;
//8 revolutions to open/close window
const int windowRevolutions = 8;

const int NBSTEPS = 4096;
const int STEPTIME = 900;

unsigned long lastTime = 0L;
unsigned int count = 0L;

String windowState = "";

int arrayDefault[4] = {LOW, LOW, LOW, LOW};

int stepsMatrix[8][4] = {
    {LOW, LOW, LOW, HIGH},
    {LOW, LOW, HIGH, HIGH},
    {LOW, LOW, HIGH, LOW},
    {LOW, HIGH, HIGH, LOW},
    {LOW, HIGH, LOW, LOW},
    {HIGH, HIGH, LOW, LOW},
    {HIGH, LOW, LOW, LOW},
    {HIGH, LOW, LOW, HIGH},
};

Pins motorPins;
//Stepper myStepper(stepsPerRevolution, motorPins.MotorPin_1, motorPins.MotorPin_2, motorPins.MotorPin_3, motorPins.MotorPin_4);

void StepperControl::StepperSetup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void writeStep(int outArray[4])
{
  digitalWrite(IN1, outArray[0]);
  digitalWrite(IN2, outArray[1]);
  digitalWrite(IN3, outArray[2]);
  digitalWrite(IN4, outArray[3]);
}

void stepper()
{

  unsigned long currentMicros;
  int stepsLeft = NBSTEPS;
  int Step = 0;
  count = 0;
  lastTime = micros();
  Serial.println("Stepper");

  while (stepsLeft > 0)
  {
    //Serial.println("while");
    currentMicros = micros();
    if (currentMicros - lastTime >= STEPTIME)
    {
      if ((Step >= 0) && (Step < 8))
      {
        writeStep(stepsMatrix[Step]);
        Serial.println("writing");
      }
      else
      {
        writeStep(arrayDefault);
      }
      count += micros() - lastTime;
      lastTime = micros();
      stepsLeft--;
      Step++;
    }
    delay(1);
  }

  delay(2000);
  stepsLeft = NBSTEPS;
}

// void setDirection(bool direction)
// {
//   (direction == true) ? (Step++) : (Step--);

//   if (Step > 7)
//   {
//     Step = 0;
//   }
//   else if (Step < 0)
//   {
//     Step = 7;
//   }
// }

void StepperControl::StepperRun(bool direction)
{

  if (direction)
  {
    if (windowState != "open")
    {
      Serial.println("~~~~~OPENING~~~~~");

     // setDirection(direction);
      Serial.println(direction);
      stepper();

      windowState = "open";
      delay(10);
    }
    else
    {
      Serial.println("Already Open");
    }
  }
  else if (direction = 2)
  {
    if (windowState != "closed")
    {
      // step one revolution in one direction:
      Serial.println("~~~~~CLOSING~~~~~");

      windowState = "closed";
      delay(10);
    }
    else
    {
      Serial.println("Already Closed");
    }
  }
}

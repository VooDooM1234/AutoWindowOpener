//#include <avr/sleep.h>

//#include "Arduino.h"
#include "Esp.h"

#include "Button.h"
#include "StepperControl.h"

const int OnBoardLED = 2;

const int OpenButton = D8;
const int CloseButton = D7;
const int DebugButton = D6;

const byte OpenDirection = 0; //Clockwise
const byte CloseDirection = 1; //Counter Clockwise

Button openButton = Button("Open", OpenButton);
Button closeButton = Button("Close", CloseButton);
Button debugButton = Button("Debug", DebugButton);

StepperControl stepper = StepperControl();

void setup()
{
  pinMode(OnBoardLED, OUTPUT);

  openButton.buttonSetup();
  closeButton.buttonSetup();
  debugButton.buttonSetup();

  Serial.begin(115200);
  Serial.print("Sanity Test ");
}

void loop()
{
  digitalWrite(2, LOW);
  //Change to list for each or whatever it is in c++
  Serial.flush();

  if (openButton.IsButtonPress() == true)
  {
    digitalWrite(2, HIGH);
    Serial.print("OPEN BUTTON: ");
    Serial.println("PRESSED!!");
    Serial.println("~~~~~");
    stepper.StepperRun(OpenDirection);
    delay(1000);
  }

  if (closeButton.IsButtonPress() == true)
  {
    digitalWrite(2, HIGH);
    Serial.print("CLOSE BUTTON: ");
    Serial.println("PRESSED!!");
    Serial.println("~~~~~");
    stepper.StepperRun(CloseDirection);
    delay(1000);
  }
  if (debugButton.IsButtonPress() == true)
  {
    digitalWrite(2, HIGH);
    Serial.print("DEBUG: ");
    Serial.println("PRESSED!!");
    Serial.println("~~~~~");
    delay(1000);
  }
  else
  {
  }
}

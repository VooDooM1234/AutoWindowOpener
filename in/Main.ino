//#include <avr/sleep.h>

//#include "Arduino.h"
#include "Esp.h"
//#include <list>
/*
//  TO BE ADDED
//  1.  ZEROING FOR MOTOR 
//  2.  SLEEP MODE FOOR ESP
//  3.  ONBOARD RTC
//  4.  HOLDING REMOTE BUTTON 
*/
#include "Button.h"
#include "StepperControl.h"
#include "IR_Control.h"
#include "StepperControl.h"
#include "Pins.h"

static const int numButtons = 3;

static const byte OpenDirection = true;  //Clockwise
static const byte CloseDirection = false; //Counter Clockwise

Pins pinsCollection;

Button openButton = Button("Open", pinsCollection.OpenButton);
Button closeButton = Button("Close", pinsCollection.CloseButton);
Button debugButton = Button("Debug", pinsCollection.DebugButton);

IR_Control remoteSensor = IR_Control("Remote Control", pinsCollection.IR_Pin);

StepperControl stepper = StepperControl();


void setup()
{
  pinMode(pinsCollection.OnBoardLED, OUTPUT);

  openButton.buttonSetup();
  closeButton.buttonSetup();
  debugButton.buttonSetup();

  stepper.StepperSetup();

  remoteSensor.IRSetup();

  Serial.begin(115200);
  Serial.print("Sanity Test ");
}

void loop()
{
  int remoteButton;
  digitalWrite(pinsCollection.OnBoardLED, LOW);

  Serial.flush();

  if (remoteSensor.IRHasRecievedData() == true)
  {
    remoteButton = remoteSensor.IR_Run();
    stepper.StepperRun(remoteButton);
  }

  if (openButton.IsButtonPress() == true)
  {
    digitalWrite(pinsCollection.OnBoardLED, HIGH);
    Serial.print("OPEN BUTTON: ");
    Serial.println("PRESSED!!");
    stepper.StepperRun(OpenDirection);
    delay(1000);
  }

  if (closeButton.IsButtonPress() == true)
  {
    digitalWrite(pinsCollection.OnBoardLED, HIGH);
    Serial.print("CLOSE BUTTON: ");
    Serial.println("PRESSED!!");
    stepper.StepperRun(CloseDirection);
    delay(1000);
  }
  if (debugButton.IsButtonPress() == true)
  {
    digitalWrite(pinsCollection.OnBoardLED, HIGH);
    Serial.print("DEBUG: ");
    Serial.println("PRESSED!!");
    delay(1000);
  }
  else
  {
  }
}

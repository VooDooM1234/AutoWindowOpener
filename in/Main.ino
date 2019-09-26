#include "Esp.h"
//#include <list>

#include "Button.h"
#include "StepperControl.h"
#include "IR_Control.h"
#include "StepperControl.h"

static const uint8_t OnBoardLED = 2;

static const uint8_t OpenButton = D8;   //15 - d8
static const uint8_t CloseButton = D7;  //13 - d7
static const uint8_t DebugButton = D6;  //12 - d6

static const uint8_t IR_Pin = D5;

static const uint8_t numButtons = 3;

static const byte OpenDirection = 0;  //Clockwise
static const byte CloseDirection = 1; //Counter Clockwise

Button openButton = Button("Open", OpenButton);
Button closeButton = Button("Close", CloseButton);
Button debugButton = Button("Debug", DebugButton);

IR_Control remoteSensor = IR_Control("Remote Control", IR_Pin);

StepperControl stepper = StepperControl();

void setup()
{
  pinMode(OnBoardLED, OUTPUT);

  openButton.buttonSetup();
  closeButton.buttonSetup();
  debugButton.buttonSetup();

  remoteSensor.IRSetup();

  Serial.begin(115200);
  Serial.print("Sanity Test ");
}

void loop()
{
  int remoteButton;
  digitalWrite(2, LOW);
  
  Serial.flush();

  if(remoteSensor.IRHasRecievedData() == true){
    remoteButton = remoteSensor.IR_Run();
    stepper.StepperRun(remoteButton);
  }

  if (openButton.IsButtonPress() == true)
  {
    digitalWrite(2, HIGH);
    Serial.print("OPEN BUTTON: ");
    Serial.println("PRESSED!!");
    stepper.StepperRun(OpenDirection);
    delay(1000);
  }

  if (closeButton.IsButtonPress() == true)
  {
    digitalWrite(2, HIGH);
    Serial.print("CLOSE BUTTON: ");
    Serial.println("PRESSED!!");
    stepper.StepperRun(CloseDirection);
    delay(1000);
  }
  if (debugButton.IsButtonPress() == true)
  {
    digitalWrite(2, HIGH);
    Serial.print("DEBUG: ");
    Serial.println("PRESSED!!");
    delay(1000);
  }
  else
  {
  }
}

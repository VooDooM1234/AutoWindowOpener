#include "Esp.h"
//#include <list>

#include "Button.h"
#include "StepperControl.h"
#include "IR_Control.h"

typedef struct pins
{
  const int OnBoardLED = 2;

  const int OpenButton = D8;
  const int CloseButton = D7;
  const int DebugButton = D6;

  const int IR_Pin = D4;

  const int MotorPin_1 = D0;
  const int MotorPin_2 = D1;
  const int MotorPin_3 = D2;
  const int MotorPin_4 = D3;
};

const int numButtons = 3;

const byte OpenDirection = 0;  //Clockwise
const byte CloseDirection = 1; //Counter Clockwise

//std::list<Button>::iterator buttons;

Button openButton = Button("Open", pins.OpenButton);
Button closeButton = Button("Close", pins.CloseButton);
Button debugButton = Button("Debug", pins.DebugButton);

IR_Control remoteSensor = IR_Control("Remote Control", pins.IR_Pin);

StepperControl stepper = StepperControl();

void setup()
{
  pinMode(pins.OnBoardLED, OUTPUT);

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

#include "Esp.h"

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

static const byte OpenDirection = true;   //Clockwise
static const byte CloseDirection = false; //Counter Clockwise

byte buffer = 0;
//inistalisation of Interrupt service routine
void ICACHE_RAM_ATTR IntCallback();

Pins pinsCollection;

Button openButton = Button("Open", pinsCollection.OpenButton);
Button closeButton = Button("Close", pinsCollection.CloseButton);
//Button debugButton = Button("Debug", pinsCollection.DebugButton);

IR_Control remoteSensor = IR_Control("Remote Control", pinsCollection.IR_Pin);

StepperControl stepper = StepperControl();

void setup()
{
  pinMode(pinsCollection.OnBoardLED, OUTPUT);

  openButton.buttonSetup();
  closeButton.buttonSetup();
  //debugButton.buttonSetup();

  attachInterrupt(digitalPinToInterrupt(pinsCollection.DebugButton), IntCallback, CHANGE);

  stepper.StepperSetup();

  remoteSensor.IRSetup();

  Serial.begin(115200);
  Serial.println("Sanity Test ");
  delay(500);
}

void loop()
{
  int remoteButton;
  digitalWrite(pinsCollection.OnBoardLED, LOW);

  //remote sensor data recived
  if (remoteSensor.IRHasRecievedData() == true)
  {
    remoteButton = remoteSensor.IR_Run();
    stepper.StepperRun(remoteButton);
  }
  //open button data recieved
  if (openButton.IsButtonPress() == true)
  {
    digitalWrite(pinsCollection.OnBoardLED, HIGH);
    //buffer for inistalisation of device clear buffer doesnt work natively on ESP for some reason
    if (buffer != 0)
    {
      Serial.print("OPEN BUTTON: ");
      Serial.println("PRESSED!!");
      stepper.StepperRun(OpenDirection);
    }
    buffer++;
    delay(100);
  }
  //close button data recieved
  if (closeButton.IsButtonPress() == true)
  {
    digitalWrite(pinsCollection.OnBoardLED, HIGH);
    Serial.print("CLOSE BUTTON: ");
    Serial.println("PRESSED!!");
    stepper.StepperRun(CloseDirection);
    delay(100);
  }
  // if (debugButton.IsButtonPress() == true)
  // {
  //   digitalWrite(pinsCollection.OnBoardLED, HIGH);
  //   Serial.print("DEBUG: ");
  //   Serial.println("PRESSED!!");
  //   delay(100);
  // }
  else
  {
  }
}

void IntCallback()
{
  Serial.println("Killing Program");
  while (openButton.IsButtonPress() != true && closeButton.IsButtonPress() != true)
  {
  }
  Serial.println("Restarting...");
}

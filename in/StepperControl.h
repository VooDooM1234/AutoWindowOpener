#ifndef StepperControl_H
#define StepperControl_H

//#include "Arduino.h"
#include "Esp.h"

#include <Stepper.h>
#include "StepperControl.h"

class StepperControl
{
private:
int pin;
String name;
public:
    StepperControl() 
    {

    }

    void StepperSetup();
    void StepperRun(byte direction);

};

extern StepperControl stepperControl;

#endif
#ifndef StepperControl_H
#define StepperControl_H

//#include "Arduino.h"
#include "Esp.h"
#include "StepperControl.h"

class StepperControl
{
private:
    void stepper(bool direction);
    void writeStep(int outArray[4]);
    bool currentStateChecker(bool direction);

    int pin;
    String name;

    // Motor not moving and soft turned off
    int arrayDefault[4] = {LOW, LOW, LOW, LOW};

    //Standard stepping matrix for 4 pin stepper motor
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

    const int stepsPerRevolution = 4096; //32 steps per rev * gear ratio of 64:1 = 2038
    const int windowRevolutions = 8;     //8 revolutions to open/close window
    // low speed (high torque) = 1465 ~= 1 rpm
    // high speed (low torque) = 600 ~=  24 rpm
    //rpm = 60000000 / (unsigned long) speed / stepsPerRevolution
    //rpm can be increased at higher input voltages (5v to 12v)
    const int speed = 600;

    const int endIndexOfStepMatrix = 7;
    const int startIndexOfStepMatric = 0;
    
    int Step = 0; //
    unsigned long lastTime = 0L;
    unsigned int motorTime = 0L;

    String windowState = "";

public:
    StepperControl()
    {
    }
    void StepperSetup();
    void StepperRun(bool direction);

    
};

//extern StepperControl stepperControl;

#endif
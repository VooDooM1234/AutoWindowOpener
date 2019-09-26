
#ifndef IR_Control_H
#define IR_Control_H
#include "Esp.h"

#include "IR_Control.h"

class IR_Control
{
private:

    int pin;
    String name;

public:
    IR_Control(String name, int attachTo) : pin(attachTo)
    {
    }
    //String IR_ButtonCheck(String data);
    void IRSetup();
    int IR_Run();
    bool IRHasRecievedData();
};

extern IR_Control IRControl;

#endif
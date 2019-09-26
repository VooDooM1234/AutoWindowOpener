
#ifndef IR_Control_H
#define IR_Control_H

#include <interrupt.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include "Esp.h"

#include "IR_Control.h"

class IR_Control
{
private:

public:
    IR_Control(String name, int attachTo) : pin(attachTo)
    {

    }
    

};

extern IR_Control IRControl;

#endif
//#include "Arduino.h"
#include "Esp.h"

#include "Button.h"


int state = HIGH;
unsigned long buttonDownMs;

Button::Button(String name, int attachTO);

void Button::buttonSetup()
{
    pinMode(pin, INPUT_PULLUP);
    state = HIGH;
}

bool Button::IsButtonPress()
{
    int prevState = state;
    state = digitalRead(pin);
    
    if (prevState == HIGH && state == LOW)
    {
       buttonDownMs = millis();
       return true;
    }
    //Button Debouncing
    else if (prevState == LOW && state == HIGH)
    {
        if (millis() - buttonDownMs < 50)
        {
            // ignore this for debounce
        }
    return false;
    }
}
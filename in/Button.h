
#ifndef Button_H
#define Button_H

//#include "Arduino.h"
#include "Esp.h"
#include "Button.h"

class Button
{
private:
int pin;
String name;

public:
  Button(String name, int attachTo) : pin(attachTo)
  {
  }

  //~Button();

  void buttonSetup();
  bool IsButtonPress();
};

extern Button button;

#endif
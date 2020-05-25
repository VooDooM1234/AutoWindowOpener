/* 
 *  Basic code working with Arduio
 */

// Include the Arduino Stepper.h library:
#include <Stepper.h>

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;
const int buttonCW = 7;     // the number of the pushbutton pin
const int buttonCCW = 6;     // the number of the pushbutton pin

int buttonStateCW = 0;
int buttonStateCCW = 0;
// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Set the speed to 5 rpm:
  myStepper.setSpeed(10);
   pinMode(buttonCW, INPUT);
   pinMode(buttonCCW, INPUT);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

void loop() {
   buttonStateCW = digitalRead(buttonCW);
    buttonStateCCW = digitalRead(buttonCCW);

   if(buttonStateCW == HIGH){
  // Step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution*10);
  delay(500);
   }else if(buttonStateCCW == HIGH){
  // Step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution*10);
  delay(500);
}else{
   myStepper.step(0);
  
}
}

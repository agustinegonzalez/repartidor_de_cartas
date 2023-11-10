#include <Stepper.h>

int stepsPerRevolution = 2048;
uint8_t motSpeed = 10;
Stepper myStepper(stepsPerRevolution,2,3,4,5);


void setup() {
  // put your setup code here, to run once:
  myStepper.setSpeed(motSpeed);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  myStepper.step(stepsPerRevolution);  
}
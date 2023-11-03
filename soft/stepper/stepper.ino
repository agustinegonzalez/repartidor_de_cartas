#include <Stepper.h>
uint16_t stepsPerRevolution = 2048;
uint8_t motSpeed = 12;


Stepper stepper(stepsPerRevolution,8,10,9,11);
uint16_t dt = 1500;

void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(motSpeed);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.step(stepsPerRevolution);
  delay(dt);
  stepper.step(-stepsPerRevolution);
  delay(dt);
  
}
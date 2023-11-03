#include <Stepper.h>
uint16_t PasosPorRevolucion = 2048;
uint8_t motSpeed = 12;


Stepper stepper(PasosPorRevolucion,2,3,4,5);
uint16_t retraso = 1500;

void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(motSpeed);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.step(PasosPorRevolucion);
  delay(retraso);
  stepper.step(PasosPorRevolucion);
  delay(retraso);
  
}
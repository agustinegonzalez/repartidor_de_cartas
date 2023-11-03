#include <Stepper.h>

uint8_t pasos_por_revolucion = 2048;
uint8_t velocidad_motor = 11;

Stepper PasoPaso(pasos_por_revolucion,8,10,9,11);




void setup() {

  PasoPaso.setSpeed(velocidad_motor);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  PasoPaso.step(pasos_por_revolucion);
}

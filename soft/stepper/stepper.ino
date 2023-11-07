#include <Stepper.h>


uint16_t PasosPorRevolucion = 2048;
uint8_t velocidad = 12;
int juego = 0;
Stepper stepper(PasosPorRevolucion, 2, 3, 4, 5);
uint16_t retraso = 1500;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(velocidad);
}

void loop() {
  // put your main code here, to run repeatedly:
  // stepper.step(PasosPorRevolucion);
  // delay(retraso);
  // stepper.step(PasosPorRevolucion);
  // delay(retraso);
  if (Serial.available() > 0) {
    juego = Serial.parseInt();  //parseInt lee un entero desde puerto serie
    juego_seleccionado(juego);
  }
}

juego_seleccionado(int juego) {
  switch(juego){
    case 1:
    //llama al a funcion correspondiente al juego 1
    break;
    case 2:
    //llama a la funcion correspondiente al juego 2
    break;
    case 3:
    //llama a la funcion correspondiente al juego 3
    break;
    default:
    break;
  }
}
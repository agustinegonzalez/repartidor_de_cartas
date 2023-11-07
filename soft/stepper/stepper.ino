#include <Stepper.h>



uint16_t PasosPorRevolucion = 2048;
uint8_t velocidad = 12;
char juego [1];
Stepper stepper(PasosPorRevolucion, 2, 3, 4, 5);
uint16_t retraso = 1500;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(velocidad);
}

void juego_seleccionado(char juego[0]) {
  switch (juego[0]) {
    case 'u':
      // Llama a la función correspondiente al juego 1 (UNO)
      Serial.println("Se llamó correctamente a la función que carga al juego. ");
      break;
    case 'r':
      // Llama a la función correspondiente al juego 2 (v)
      break;
    case 'c':
      // Llama a la función correspondiente al juego 3 (a)
      break;
    default:
      // Manejar otros casos o errores
      break;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  // stepper.step(PasosPorRevolucion);
  // delay(retraso);
  // stepper.step(PasosPorRevolucion);
  // delay(retraso);
  size_t n;
  char letra[1];

  n = Serial.readBytes(letra,1);

  if( n == 1){
    juego_seleccionado(letra[0]);
  }
}


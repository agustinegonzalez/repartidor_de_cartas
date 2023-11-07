/*#include <Stepper.h>



uint16_t PasosPorRevolucion = 2048;
uint8_t velocidad = 12;
char juego [1];
Stepper stepper(PasosPorRevolucion, 2, 3, 4, 5);
uint16_t retraso = 1500;
*/
void setup() {
  Serial.begin(9600);
  //stepper.setSpeed(velocidad);
}

void loop() {
 
 if (Serial.available() > 0) {
        char cadenaLeida[32]; 
        int i = 0;

        while (Serial.available() > 0) {
            char caracterLeido = Serial.read();
            cadenaLeida[i] = caracterLeido;
            i++;
        }
        cadenaLeida[i] = '\0'; // Agrega un carácter nulo al final para formar una cadena

        // Realiza acciones en función de la cadena completa recibida
        if (strcmp(cadenaLeida, "UNO") == 0) {
            // Realiza una acción específica para "UNO"
            Serial.print("HOLA");
        }
    }
}


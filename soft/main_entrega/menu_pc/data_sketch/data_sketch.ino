void setup() {
  // Inicializar el puerto serie a una velocidad específica (en baudios)
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String cadena = Serial.readStringUntil('\n');
    cadena.trim(); // Eliminar espacios en blanco, incluido el '\n' al final

    if (cadena == "Cargado") { // Cambié las comillas simples por comillas dobles
      int numero = 123; // Puedes cambiar este número según tus necesidades
      Serial.print(numero);
    }
  }
}

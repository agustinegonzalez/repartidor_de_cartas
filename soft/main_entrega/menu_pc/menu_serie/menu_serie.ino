void setup() {
  // Inicializar el puerto serie a una velocidad específica (en baudios)
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String cadena = readStringUntil('\n');
    if (cadena == 'Cargado') {
      int numero = 123; // Puedes cambiar este número según tus necesidades
      Serial.print(numero);
    }
  }
}

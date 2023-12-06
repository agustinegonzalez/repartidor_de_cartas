void setup() {
  // Inicializar el puerto serie a una velocidad específica (en baudios)
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == 'a') {
      int numero = 123; // Puedes cambiar este número según tus necesidades
      Serial.print(numero);
    }
  }
}

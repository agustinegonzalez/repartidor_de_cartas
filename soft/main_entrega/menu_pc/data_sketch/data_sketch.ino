void setup() {
  // Inicializar el puerto serie a una velocidad específica (en baudios)
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String cadena = Serial.readString();
    cadena.trim();

    if (cadena == "Cargado") { // Cambié las comillas simples por comillas dobles
      Serial.println("Recibido");
    }
  }
}

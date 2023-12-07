void setup(){

  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0) {
    String cadena = Serial.readString();
    cadena.trim();

    if (cadena == "Cargado") {
      Serial.println("Recibido");
    }
  }
}


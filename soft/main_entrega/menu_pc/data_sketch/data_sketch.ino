void setup(){
  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0) {
    String cadena = Serial.readString();

    if (cadena == "Cargado") {
      Serial.println("Recibido");
      }
  }
}


void setup(){
<<<<<<< HEAD
=======

>>>>>>> main
  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0) {
    String cadena = Serial.readString();
<<<<<<< HEAD

    if (cadena == "Cargado") {
      Serial.println("Recibido");
      }
=======
    cadena.trim();

    if (cadena == "Cargado") {
      Serial.println("Recibido");
    }
>>>>>>> main
  }
}


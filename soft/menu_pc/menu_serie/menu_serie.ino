void setup() {
    Serial.begin(9600); // Inicia el puerto serie a 9600 bps
}

void loop() {
    if (Serial.available()) {
        String juegoserie = Serial.readStringUntil('\n');
        Serial.print("Cadena recibida: ");
        Serial.println(juegoserie);
    }
}
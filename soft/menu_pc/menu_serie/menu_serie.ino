void setup() {
    Serial.begin(9600); 
}

void loop() {
    if (Serial.available()) {
        String juegoserie = Serial.readStringUntil('\n');
        Serial.println(juegoserie);
    }
}
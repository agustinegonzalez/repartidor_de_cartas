#include <Stepper.h> //incluyo libreria para motor paso a paso

#include <EEPROM.h>//incluyo libreria para poder acceder a la memoria eeprom del arduino

#include <Wire.h> //incluyo libreria para la comunicacion I2C
#include <LiquidCrystal_I2C.h> //incluyo libreria para display I2C
#include <Servo.h> //incluyo libreria para servo motor


//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //
//Se llama la librería del servo

//Pin a conectar el servo
int pinServo = 10;

//Se crea un nuevo objeto del servo
Servo servo;
// Esto es el número de pasos por revolución
#define STEPS 4096 
// Número de pasos que queremos que de
#define NUMSTEPS 4000
  
// Constructor, pasamos STEPS y los pines donde tengamos conectado el motor
Stepper stepper(STEPS, 2, 3, 4, 5);
void setup() {
  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  // Escribimos el Mensaje en el LCD.
  lcd.print("Tiempo en caminar");
  servo.attach(pinServo);
  Serial.begin(9600);
  // Asignamos la velocidad en RPM (Revoluciones por Minuto)
  stepper.setSpeed(5);
}

void loop() {
   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
   // Escribimos el número de segundos trascurridos
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  delay(100);
  //Movemos el servomotor a 10°
  servo.write(10);
  delay(2000);
  //Leemos la posición de servomotor y la mostramos
  Serial.println(servo.read());
  servo.write(90);
  delay(2000);
  Serial.println(servo.read());
  servo.write(160);
  delay(2000);
  Serial.println(servo.read());
   // Movemos el motor un número determinado de pasos
  stepper.step(NUMSTEPS);
  delay(2000);
}

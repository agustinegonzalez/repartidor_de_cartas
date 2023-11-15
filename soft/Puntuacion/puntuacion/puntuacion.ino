#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27

// Inicialización del LCD
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

const int botonIncrementarJugador1Pin = 8; //Pin donde se encuentra el pulsador de incremento J1
const int botonIncrementarJugador2Pin = 9;//Pin donde se encuentra el pulsador de incremento J2

byte puntuacionJugador1 = 0; //variable puntuacion jugador1
byte puntuacionJugador2 = 0; //variable puntuacion jugador2

void setup() {
  lcd.init(); //Inicia Display
  lcd.backlight(); //Enciende luz display

  pinMode(botonIncrementarJugador1Pin, INPUT_PULLUP); //declara el pin con un resistencia de entrada pullup
  pinMode(botonIncrementarJugador2Pin, INPUT_PULLUP); //declara el pin con un resistencia de entrada pullup
}

void loop() {
  mostrarPuntuacion(); //llama a la funcion que muestra la puntuacion

  if (digitalRead(botonIncrementarJugador1Pin) == HIGH) { //Si el boton se presiona, accede al if
    delay(200); // Debounce para evitar lecturas erróneas debido a rebotes
    puntuacionJugador1++; //Incrementa en 1 la puntuacion del jugador 1
  }

  if (digitalRead(botonIncrementarJugador2Pin) == HIGH ) { //Si el boton se presiona, accede al if
    delay(200);
    puntuacionJugador2++; // Incrementa en 1 la puntuacion del jugador 2
  }
}

void mostrarPuntuacion() {
  lcd.clear(); //Limpia la pantalla del lcd

  // Mostrar la puntuación del jugador 1 en la primera línea del LCD
  lcd.setCursor(0, 0);
  lcd.print("Jugador 1: ");
  lcd.print(puntuacionJugador1);

  // Mostrar la puntuación del jugador 2 en la segunda línea del LCD
  lcd.setCursor(0, 1);
  lcd.print("Jugador 2: ");
  lcd.print(puntuacionJugador2);
}

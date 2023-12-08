#include <LiquidMenu.h>
#include <Wire.h> //incluyo libreria para la comunicacion I2C
#include <LiquidCrystal_I2C.h> //incluyo libreria para display I2C
#include <Stepper.h>

#define LCD_DIRECCION 0x27
#define LCD_DIRECCION2 0x20

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

uint8_t lcd_columnas = 16;
uint8_t lcd_filas = 2;
LiquidCrystal_I2C lcd(LCD_DIRECCION, lcd_columnas, lcd_filas); // Crea una instancia de LiquidCrystal_I2C
LiquidCrystal_I2C lcd2(LCD_DIRECCION2, lcd_columnas, lcd_filas); // Crea una instancia de LiquidCrystal_I2C para el display 2

uint8_t vueltas = 0;

boolean accionado = false;
int  PulsadorUP = 7;    // pin del Pulsador incrementador
int  PulsadorDOWN = 8;    // pin del Pulsador decrementador
int PulsadorOK = 9;    // pin del Pulsador reset

const int botonIncrementarJugador1Pin = 12; //Pin donde se encuentra el pulsador de incremento J1
const int botonIncrementarJugador2Pin = 11;//Pin donde se encuentra el pulsador de incremento J2
byte puntuacionJugador1 = 0; //variable puntuacion jugador1
byte puntuacionJugador2 = 0; //variable puntuacion jugador2


LiquidLine linea1(1, 0, "UNO");
LiquidLine linea2(1, 1, "POKER");
LiquidLine linea3(1, 0, "RUMI");
LiquidLine linea4(1, 1, "INGRESO MANUAL");
LiquidScreen pantalla1(linea1, linea2, linea3, linea4);

LiquidLine linea1_2(1, 0, "2 Jugadores");
LiquidLine linea2_2(1, 1, "3 Jugadores");
LiquidLine linea3_2(1, 0, "4 Jugadores");
LiquidLine linea4_2(1, 1, "Volver");
LiquidScreen pantalla2(linea1_2, linea2_2, linea3_2, linea4_2);

LiquidLine linea1_3(1, 0, "3 cartas");
LiquidLine linea2_3(1, 1, "4 cartas");
LiquidLine linea3_3(1, 0, "7 cartas");
LiquidLine linea4_3(1, 1, "Volver");

LiquidScreen pantalla3(linea1_3, linea2_3, linea3_3, linea4_3);


LiquidMenu menu(lcd, pantalla1, pantalla2, pantalla3); // Crea una instancia de LiquidMenu utilizando lcd


void setup() {
  pinMode(PulsadorUP, INPUT); //pin Pulsador configurado como entrada con resistencia de pullup interna
  pinMode(PulsadorDOWN, INPUT ); //pin Pulsador configurado como entrada con resistencia de pullup interna
  pinMode(PulsadorOK, INPUT); //pin Pulsador configurado como entrada con resistencia de pullup interna
  pinMode(botonIncrementarJugador1Pin, INPUT); //declara el pin con un resistencia de entrada pullup
  pinMode(botonIncrementarJugador2Pin, INPUT_PULLUP); //declara el pin con un resistencia de entrada pullup
  pinMode(A1, OUTPUT);

  // Iniciar la comunicación serial a 9600 baudios
  Serial.begin(9600);

  // Inicializar el LCD
  lcd.init(); //Inicia Display
  lcd2.init(); //Inicia Display2

  //Encender la luz de fondo.
  lcd.backlight(); //Enciende luz display
  lcd2.backlight(); //Enciende luz display

  //selecciona donde se ubica el cursor
  linea1.set_focusPosition(Position::LEFT);
  linea2.set_focusPosition(Position::LEFT);
  linea3.set_focusPosition(Position::LEFT);
  linea4.set_focusPosition(Position::LEFT);
  //segun la opcion ejecuta con una funcion con la funcion attach
  linea1.attach_function(1, juego1);
  linea2.attach_function(1, juego2);
  linea3.attach_function(1, juego3);
  linea4.attach_function(1, manual);

  menu.add_screen(pantalla1);

  //selecciona donde se ubica el cursor
  linea1_2.set_focusPosition(Position::LEFT);
  linea2_2.set_focusPosition(Position::LEFT);
  linea3_2.set_focusPosition(Position::LEFT);
  linea4_2.set_focusPosition(Position::LEFT);
  //segun la opcion ejecuta con una funcion con la funcion attach
  linea1_2.attach_function(1, fn_2jugadores);
  linea2_2.attach_function(1, fn_3jugadores);
  linea3_2.attach_function(1, fn_4jugadores);
  linea4_2.attach_function(1, volver);

  menu.add_screen(pantalla2);

  //selecciona donde se ubica el cursor
  linea1_3.set_focusPosition(Position::LEFT);
  linea2_3.set_focusPosition(Position::LEFT);
  linea3_3.set_focusPosition(Position::LEFT);
  linea4_3.set_focusPosition(Position::LEFT);
  //segun la opcion ejecuta con una funcion con la funcion attach
  linea1_3.attach_function(1, fn_2cartas);
  linea2_3.attach_function(1, fn_3cartas);
  linea3_3.attach_function(1, fn_4cartas);
  linea4_3.attach_function(1, volvermanual);

  menu.add_screen(pantalla3);


  pantalla1.set_displayLineCount(2); //selecciona la cantidad que tiene nuestro display para la pantalla 1
  pantalla2.set_displayLineCount(2);//selecciona la cantidad que tiene nuestro display para la pantalla 2
  pantalla3.set_displayLineCount(2);//selecciona la cantidad que tiene nuestro display para la pantalla 3


  menu.set_focusedLine(0); // pone el foco del menu en 0
  menu.update(); //actualiza la info que se muestra en el display


  myStepper.setSpeed(12); //setea la velocidad en 12
}

void loop() {

  //Botones Menu
  if ((digitalRead (PulsadorUP) == HIGH) && accionado == false) { //llamado a funcion incrementar
    menu.switch_focus(true); //hace que el cursor baje
    menu.update(); //actualiza la info que se muestra en el display

    accionado = true;
  }
  if ((digitalRead (PulsadorDOWN) == HIGH) && accionado == false) { //llamado a funcion decrementar
    menu.switch_focus(false); //hace que el robot suba
    menu.update(); //actualiza la info que se muestra en el display

    accionado = true;
  }
  if ((digitalRead (PulsadorOK) == HIGH) && accionado == false) { //llamado a funcion reset
    menu.call_function(1);
    delay(500);
    accionado = true;
  }
  if (digitalRead(PulsadorUP)  == LOW && digitalRead (PulsadorDOWN) == LOW && digitalRead (PulsadorOK) == LOW) {  //si un pulsador esta accionado los demas no pueden estar accionados
    accionado = false;
  }

  mostrarPuntuacion(); //llama a la funcion que muestra la puntuacion

  //Botones Puntuacion
  if (digitalRead(botonIncrementarJugador1Pin) == HIGH) { //Si el boton se presiona, accede al if
    delay(200); // Debounce para evitar lecturas erróneas debido a rebotes
    puntuacionJugador1++; //Incrementa en 1 la puntuacion del jugador 1
  }

  if (digitalRead(botonIncrementarJugador2Pin) == HIGH ) { //Si el boton se presiona, accede al if
    delay(200);
    puntuacionJugador2++; // Incrementa en 1 la puntuacion del jugador 2
  }



}
void juego1() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  vueltas = 7;
}
void juego2() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  vueltas = 2;
}
void juego3() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  vueltas = 10;
}
void manual() {
  menu.change_screen(3);
  menu.set_focusedLine(0);

}
void fn_2cartas() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  vueltas = 2;
}
void fn_3cartas() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  vueltas = 3;
}
void fn_4cartas() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  vueltas = 4;
}
void fn_5cartas() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  vueltas = 5;
}


void fn_2jugadores() {
  for (int z = 0; z < vueltas ; z++) {
    for (int i = 0; i < 2; i++) {
      myStepper.step(stepsPerRevolution / 2);
      delay (500);
      digitalWrite(A1, HIGH);
      delay(500);
      digitalWrite(A1, LOW);

    }
  }
}
void fn_3jugadores() {
  for (int z = 0; z < vueltas ; z++) {
    for (int i = 0; i < 3; i++) {
      myStepper.step(stepsPerRevolution / 3);
      delay (500);
      digitalWrite(A1, HIGH);
      delay(500);
      digitalWrite(A1, LOW);
    }
  }
}
void fn_4jugadores() {
  for (int z = 0; z < vueltas ; z++) {
    for (int i = 0; i < 4; i++) {
      myStepper.step(stepsPerRevolution / 4);
      delay (500);
      digitalWrite(A1, HIGH);
      delay(500);
      digitalWrite(A1, LOW);
    }
  }
}


void volvermanual() {
  menu.change_screen(1);
}
void volver() {
  menu.previous_screen();
}

void mostrarPuntuacion() {
  lcd2.clear(); //Limpia la pantalla del lcd

  // Mostrar la puntuación del jugador 1 en la primera línea del LCD
  lcd2.setCursor(0, 0);
  lcd2.print("Jugador 1: ");
  lcd2.print(puntuacionJugador1);

  // Mostrar la puntuación del jugador 2 en la segunda línea del LCD
  lcd2.setCursor(0, 1);
  lcd2.print("Jugador 2: ");
  lcd2.print(puntuacionJugador2);
}

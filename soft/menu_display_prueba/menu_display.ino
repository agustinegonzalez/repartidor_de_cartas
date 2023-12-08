#include <LiquidMenu.h>
#include <Wire.h> //incluyo libreria para la comunicacion I2C
#include <LiquidCrystal_I2C.h> //incluyo libreria para display I2C
#define LCD_DIRECCION 0x27
#include <Stepper.h>
uint8_t x = 0;
const int stepsPerRevolution = 2048;
uint8_t lcd_columnas = 16;
uint8_t lcd_filas = 2;



Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);


LiquidCrystal_I2C lcd(LCD_DIRECCION, lcd_columnas, lcd_filas); // Crea una instancia de LiquidCrystal_I2C

boolean accionado = false;
int  PulsadorUP = 7;    // pin del Pulsador incrementador
int  PulsadorDOWN = 8;    // pin del Pulsador decrementador
int PulsadorOK = 9;    // pin del Pulsador reset


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
  pinMode(A1, OUTPUT);

  // Iniciar la comunicación serial a 9600 baudios
  Serial.begin(9600);

  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
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

  

}
void juego1() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  x = 7;
}
void juego2() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  x = 2;
}
void juego3() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  x = 10;
}
void manual() {
  menu.change_screen(3);
  menu.set_focusedLine(0);

}
void fn_2cartas() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  x = 2;
}
void fn_3cartas() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  x = 3;
}
void fn_4cartas() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  x = 4;
}
void fn_5cartas() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
  x = 5;
}


void fn_2jugadores() {
  for (int z = 0; z < x ; z++) {
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
  for (int z = 0; z < x ; z++) {
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
  for (int z = 0; z < x ; z++) {
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

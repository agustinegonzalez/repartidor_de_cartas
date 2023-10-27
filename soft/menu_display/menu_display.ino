
#include <Wire.h> //incluyo libreria para la comunicacion I2C
#include <LiquidCrystal_I2C.h> //incluyo libreria para display I2C

uint8_t lcd_direccion = 39;
uint8_t lcd_columnas = 16;
uint8_t lcd_filas = 2;

LiquidCrystal_I2C lcd(lcd_direccion, lcd_columnas, lcd_filas); // Crea una instancia de LiquidCrystal_I2C

boolean accionado = false;
int  PulsadorUP = 7;    // pin del Pulsador incrementador
int  PulsadorDOWN = 8;    // pin del Pulsador decrementador
int PulsadorOK = 9;    // pin del Pulsador reset

LiquidLine linea1(1, 0, "2 Jugadores");
LiquidLine linea2(1, 1, "3 Jugadores");
LiquidLine linea3(1, 0, "4 Jugadores");
LiquidLine linea4(1, 1, "5 Jugadores");
LiquidScreen pantalla1(linea1, linea2, linea3, linea4);

LiquidLine linea1_2(1, 0, "3 Cartas");
LiquidLine linea2_2(1, 1, "4 Cartas");
LiquidLine linea3_2(1, 0, "5 cartas");
LiquidScreen pantalla2(linea1_2, linea2_2, linea3_2);


//(Agustin)Hay un problema con este tipo de declaracion. Se deberia revisar la documentacion porque con las versiones seguro fue variando.
//Compilation error: no matching function for call to 'LiquidMenu::LiquidMenu(LiquidCrystal_I2C&, LiquidScreen&, LiquidScreen&)'
//es el unico error que tira
LiquidMenu menu(lcd, pantalla1, pantalla2); // Crea una instancia de LiquidMenu utilizando lcd




void setup() {
  pinMode(PulsadorUP, INPUT); //pin Pulsador configurado como entrada con resistencia de pullup interna
  pinMode(PulsadorDOWN, INPUT ); //pin Pulsador configurado como entrada con resistencia de pullup interna
  pinMode(PulsadorOK, INPUT); //pin Pulsador configurado como entrada con resistencia de pullup interna
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
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
  linea1.attach_function(1, fn_2j);
  linea2.attach_function(1, fn_3j);
  linea3.attach_function(1, fn_4j);
  linea4.attach_function(1, fn_5j);

  //menu.add_screen(pantalla1);
  //selecciona donde se ubica el cursor
  linea1_2.set_focusPosition(Position::LEFT);
  linea2_2.set_focusPosition(Position::LEFT);
  linea3_2.set_focusPosition(Position::LEFT);
  //segun la opcion ejecuta con una funcion con la funcion attach
  linea1_2.attach_function(1, fn_3c);
  linea2_2.attach_function(1, fn_4c);
  linea3_2.attach_function(1, fn_5c);

  //menu.add_screen(pantalla2);


  pantalla1.set_displayLineCount(2); //selecciona la cantidad que tiene nuestro display para la pantalla 1
  pantalla2.set_displayLineCount(2);//selecciona la cantidad que tiene nuestro display para la pantalla 2

 // menu.set_focusedLine(0); // pone el foco del menu en 0

  //menu.update(); //actualiza la info que se muestra en el display



}

void loop() {

  if ((digitalRead (PulsadorUP) == HIGH) && accionado == false) { //llamado a funcion incrementar
    //menu.switch_focus(true); //hace que el cursor baje
    //menu.update(); //actualiza la info que se muestra en el display

    accionado = true;
  }
  if ((digitalRead (PulsadorDOWN) == HIGH) && accionado == false) { //llamado a funcion decrementar
    //menu.switch_focus(false); //hace que el robot suba
   // menu.update(); //actualiza la info que se muestra en el display

    accionado = true;
  }
  if ((digitalRead (PulsadorOK) == HIGH) && accionado == false) { //llamado a funcion reset
   // menu.call_function(1);
    delay(500);
    accionado = true;
  }
  if (digitalRead(PulsadorUP)  == LOW && digitalRead (PulsadorDOWN) == LOW && digitalRead (PulsadorOK) == LOW) {  //si un pulsador esta accionado los demas no pueden estar accionados
    accionado = false;
  }

}
void fn_2j() {
 // menu.change_screen(2);
 // menu.set_focusedLine(0);

}
void fn_3j() {
  //menu.change_screen(2);
  //menu.set_focusedLine(0);

}
void fn_4j() {
  //menu.change_screen(2);
  //menu.set_focusedLine(0);

}
void fn_5j() {
  //menu.change_screen(2);
  //menu.set_focusedLine(0);

}
void fn_3c() {
digitalWrite(A1,HIGH);
digitalWrite(A2,HIGH);
delay(3000);
digitalWrite(A1,LOW);
digitalWrite(A2,LOW);
}
void fn_4c() {
digitalWrite(A1,HIGH);
digitalWrite(A2,HIGH);
delay(3000);
digitalWrite(A1,LOW);
digitalWrite(A2,LOW);
}
void fn_5c() {
digitalWrite(A1,HIGH);
digitalWrite(A2,HIGH);
delay(3000);
digitalWrite(A1,LOW);
digitalWrite(A2,LOW);
}

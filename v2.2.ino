
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

int randNum;

// usa la dirección por defecto 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//declaramos el numero del servo shield en el que está cada servo

#define HOMBROIZQ 0
#define PIEIZQ 4
#define TOBILLOIZQ 3
#define RODILLAIZQ 2
#define PELVISIZQ 1

#define CADERA 15

#define HOMBRODER 8
#define PIEDER 12
#define TOBILLODER 11
#define RODILLADER 10
#define PELVISDER 9

//declaramos las distancias
#define CERCA 13
#define LEJOS 70
#define tiempo 300

// Ultrasonido

int inputUltrasonido = A2; // Entra en arduino (echo)
int outputUltrasonido = A3; // Sale de arduino (trig)
int distanciaUltrasonido = 0; // Recoge la distancia detectada por el ultrasonido

const int EchoPin = 5;
const int TriggerPin = 6;
const int LedPin = 13;

void setup() {
  
  // Ultrasonido

  pinMode(inputUltrasonido, INPUT);
  pinMode(outputUltrasonido  , OUTPUT);

  randomSeed(analogRead(0));
  
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
  
  pinMode(LedPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  
  erguir();
  delay(500);
  /*
  delay(250);  
  cojeraIzq();
  delay(300);
  pasitoDer();
  delay(300);
  cojeraDer();
  delay(300);
  pasoIzq();
  */
}

// FUNCIONES MOTORAS

void brazosAvance(){
  pwm.setPWM(HOMBROIZQ, 0, 620);
  pwm.setPWM(HOMBRODER, 0, 180);
}

void caderaFrente(){
  pwm.setPWM(CADERA, 0, 380);
  brazosAvance(); 
}

void caderaLigeraDer(){
  pwm.setPWM(CADERA, 0, 310);
  pwm.setPWM(HOMBROIZQ, 0, 440); // SACAMOS BRAZO IZQUIERDO
  pwm.setPWM(HOMBRODER, 0, 160); // METEMOS BRAZO DERECHO
}

void caderaLigeraIzq(){                 //\\ NECESITA CORRECCIÓN\\//
  pwm.setPWM(CADERA, 0, 450);
  pwm.setPWM(HOMBROIZQ, 0, 620); // METEMOS BRAZO IZQUIERDO
  pwm.setPWM(HOMBRODER, 0, 340); // SACAMOS BRAZO DERECHO
}

void cojeraIzq(){
  pwm.setPWM(RODILLADER, 0, 140); // ESTIRAMOS LA RODILLA DERECHA
  delay(25);
  pwm.setPWM(PELVISDER, 0, 325); // ESTIRAMOS LA PELVIS DERECHA
  delay(25);
  pwm.setPWM(PIEDER, 0, 120); // METEMOS PIE DERECHO
  delay(25);
  pwm.setPWM(PIEIZQ, 0, 365); // SACAMOS PIE IZQUIERDO
  delay(25);
}

void cojeraIzqTrasPaso(){
  pwm.setPWM(RODILLADER, 0, 140); // ESTIRAMOS LA RODILLA DERECHA
  delay(25);
  //pwm.setPWM(PELVISDER, 0, 325); // ESTIRAMOS LA PELVIS DERECHA
  delay(25);
  pwm.setPWM(PIEDER, 0, 120); // METEMOS PIE DERECHO
  delay(25);
  pwm.setPWM(PIEIZQ, 0, 365); // SACAMOS PIE IZQUIERDO
  delay(25);
}

void cojeraDer(){
  // ESTO VA DESPUÉS DE PASITO DERECHO
  delay(100);
  pwm.setPWM(RODILLAIZQ, 0, 440); // ESTIRAMOS LA RODILLA IZQUIERDA
  delay(25);
  //pwm.setPWM(TOBILLODER, 0, 320); // GIRAMOS TOBILLO DERECHO HORARIO
  delay(25);
  pwm.setPWM(PIEIZQ, 0, 530); // METEMOS PIE IZQUIERD0
  delay(100);
  //pwm.setPWM(TOBILLOIZQ, 0, 475); // ESTABILIZAMOS TOBILLO DERECHO
  delay(25);
  pwm.setPWM(PIEDER, 0, 265); // "ESTABILIZAMOS" PIE DERECHO
  delay(25);
  pwm.setPWM(PELVISIZQ, 0, 200); // ESTIRAMOS LA PELVIS IZQUIERDA
  delay(25);
  pwm.setPWM(PELVISDER, 0, 410); // CONTRAEMOS LA PELVIS DERECHA
  delay(25);
  pwm.setPWM(RODILLADER, 0, 175); // CONTRAEMOS LA RODILLA DERECHA
}

void pasitoDer(){
  // PASITO: ESTADO ESTABLE -> ESTADO PASO HACIA DELANTE
  // PASO: ESTADO PASO HACIA DELANTE -> ESTADO PASO HACIA DELANTE
  delay(100);
  caderaLigeraDer();
  pwm.setPWM(PELVISDER, 0, 395); // CONTRAEMOS PELVIS DERECHA
  delay(25);
  pwm.setPWM(RODILLADER, 0, 195); // CONTRAEMOS RODILLA DERECHA
  delay(25);
  pwm.setPWM(PELVISIZQ, 0, 185); // ¿ESTIRAMOS? PELVIS IZQUIERDA
  delay(25);
  pwm.setPWM(TOBILLOIZQ, 0, 550); // GIRAMOS TOBILLO IZQUIERDO ANTIHORARIO
  delay(25);
  pwm.setPWM(TOBILLODER, 0, 395); // GIRAMOS TOBILLO DERECHO HORARIO
  delay(100);
  pwm.setPWM(PIEDER, 0, 255); // ESTABILIZAMOS PIE DERECHO
}

void pasoDer(){                 //\\ NECESITA CORRECCIÓN\\//
  // PASITO: ESTADO ESTABLE -> ESTADO PASO HACIA DELANTE
  // PASO: ESTADO PASO HACIA DELANTE -> ESTADO PASO HACIA DELANTE
  delay(100);
  caderaLigeraDer();
  pwm.setPWM(PELVISDER, 0, 395); // CONTRAEMOS PELVIS DERECHA
  delay(25);
  pwm.setPWM(RODILLADER, 0, 195); // CONTRAEMOS RODILLA DERECHA
  delay(25);
  pwm.setPWM(RODILLAIZQ, 0, 380); // CONTRAEMOS RODILLA IZQUIERDA
  delay(20);
  pwm.setPWM(PELVISIZQ, 0, 185); // ¿ESTIRAMOS? PELVIS IZQUIERDA
  delay(25);
  pwm.setPWM(TOBILLOIZQ, 0, 550); // GIRAMOS TOBILLO IZQUIERDO ANTIHORARIO
  delay(25);
  pwm.setPWM(TOBILLODER, 0, 420); // GIRAMOS TOBILLO DERECHO HORARIO
  delay(50);
  pwm.setPWM(PIEDER, 0, 250); // ESTABILIZAMOS PIE DERECHO
}

void pasoIzq(){                  //\\ NECESITA CORRECCIÓN\\//
  // PASITO: ESTADO ESTABLE -> ESTADO PASO HACIA DELANTE
  // PASO: ESTADO PASO HACIA DELANTE -> ESTADO PASO HACIA DELANTE
  caderaLigeraIzq();
  pwm.setPWM(TOBILLODER, 0, 275); // GIRAMOS TOBILLO DERECHO ANTIHORARIO  
  delay(20);
  pwm.setPWM(RODILLAIZQ, 0, 405); // CONTRAEMOS RODILLA IZQUIERDA
  delay(20);
  pwm.setPWM(RODILLADER, 0, 210); // ESTIRAMOS RODILLA DERECHA
  delay(20);
  delay(200);
  pwm.setPWM(TOBILLOIZQ, 0, 430); // GIRAMOS TOBILLO IZQUIERDO ANTIHORARIO
  delay(100);
  pwm.setPWM(PELVISIZQ, 0, 175); // CONTRAEMOS PELVIS IZQUIERDA
  delay(20);
  pwm.setPWM(PIEIZQ, 0, 380); // ESTABILIZAMOS PIE IZQUIERDO
  delay(20);
  pwm.setPWM(PIEDER, 0, 275); // "ESTABILIZAMOS" (SACAMOS) PIE DERECHO
  delay(20);
  pwm.setPWM(PELVISDER, 0, 390); // CONTRAEMOS PELVIS DERECHA
  delay(20);
}

void erguir(){
  caderaFrente();
  pwm.setPWM(PIEDER, 0, 260);
  //delay(25);
  pwm.setPWM(PIEIZQ, 0, 380);
  //delay(25);
  pwm.setPWM(TOBILLODER, 0, 320);
  //delay(25);
  pwm.setPWM(TOBILLOIZQ, 0, 475);
  //delay(25);
  pwm.setPWM(RODILLADER, 0, 195);
  //delay(25);
  pwm.setPWM(RODILLAIZQ, 0, 405);
  //delay(25);
  pwm.setPWM(PELVISDER, 0, 395);
  //delay(25);
  pwm.setPWM(PELVISIZQ, 0, 185);
  //delay(25);
}

void loop(){
 delay(1000);
  cojeraIzqTrasPaso();
  delay(1000);
  pasoDer();
  delay(1000);
  cojeraDer();
  delay(1000);
  pasoIzq();
}


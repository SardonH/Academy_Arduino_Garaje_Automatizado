#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
Stepper motor(2048, 8, 10, 9, 11);

const int trig = 2;
const int echo = 3;
const int ledVerde = 6;   
const int ledRojo = 5;    

bool puertaAbierta = false;

void setup() {

  pinMode(2, OUTPUT); //TRIG del ultrasonido
  pinMode(3, INPUT); //ECHO del ultrasonido
  pinMode(6, OUTPUT);  //Led Verde 
  pinMode(5, OUTPUT);  //Led rojo

  motor.setSpeed(15); //Velocidad del motor Stepper

  lcd.init();
  lcd.backlight();
}

void loop() {
  int distancia = medirDistancia();

  if (distancia < 20 && puertaAbierta == false) { //Caso en el que hay un objeto delante de la puerta
    //Abrir la puerta 
    motor.step(-512);
    puertaAbierta = true;
    //Mostrar el estado de la puerta en la LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Garaje:");
    lcd.setCursor(0, 1);
    lcd.print("ABIERTO  ");
    //Mostrar el estado de la puerta en las LEDs
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);


  } else if (distancia >= 20 && puertaAbierta == true) { //Caso en el que no hay un objeto delante de la puerta
    //Cerrar la puerta 
    motor.step(512);
    puertaAbierta = false;
    //Mostrar el estado de la puerta en la LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Garaje:");
    lcd.setCursor(0, 1);
    lcd.print("CERRADO  ");
    //Mostrar el estado de la puerta en las LEDs
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);

  }
    delay(300);
}

int medirDistancia() {  //Función que mide la distancia, 
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);

  long duracion = pulseIn(3, HIGH);
  return duracion * 0.034 / 2;
}

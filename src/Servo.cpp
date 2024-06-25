#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Servo.h"

Servo::Servo(uint8_t PIN, float Frequenz, bool winkel) {
  pin = PIN;
  double konvert = 1e6/Frequenz;
  Periodendauer_ms = round(konvert); //ms
  pinMode(pin,OUTPUT);
  Winkel(winkel);
  micros_alt = micros();
}


void Servo::Winkel(bool offen) { 

  uint16_t obere_grenze = 700; //ms
  uint16_t untere_grenze = 1060; //ms

  if (offen) {
    Einschaltdauer = obere_grenze;
  } else {
    Einschaltdauer = untere_grenze;
  }
}


void Servo::einstellen() { //Serial.begin() in setup
  if (Serial.available()) {
    delay(5);
    String input = "";
    while (Serial.available())
      input+=(char)Serial.read();

    Einschaltdauer = input.toInt();
  }
}


void Servo::Halten() { // PWM
  if (micros()-micros_alt >= Periodendauer_ms) {// prüft ob eine Periode vergangen ist
    //PWM Signal 
    micros_alt = micros();
    digitalWrite(pin, HIGH);
    delayMicroseconds(Einschaltdauer);
    digitalWrite(pin, LOW);
  }
}
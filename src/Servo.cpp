#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Servo.h"

servo::servo(uint8_t PIN, float Frequenz, bool in_Winkel)
{
  pin = PIN;
  double konvert = 1e6/Frequenz;
  Periodendauer_ms = round(konvert); //ms
  pinMode(pin,OUTPUT);
  Winkel(in_Winkel);
  micros_alt = micros();
}

void servo::Winkel(bool winkel) {
    uint16_t obere_grenze = 1425; // = 120°
    uint16_t untere_grenze = 2000; // = 60°
  if (winkel){
    Einschaltdauer = obere_grenze;
  } else {
    Einschaltdauer = untere_grenze;
  }
}

void servo::Halten()
{
  if (micros()-micros_alt >= Periodendauer_ms)
  {
    micros_alt = micros();
    digitalWrite(pin, HIGH);
    delayMicroseconds(Einschaltdauer);
    digitalWrite(pin, LOW);
  }
}
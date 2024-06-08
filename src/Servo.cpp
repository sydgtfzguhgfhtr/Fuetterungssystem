#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Servo.h"

servo::servo(uint8_t PIN, float Frequenz) {
  pin = PIN;
  double konvert = 1e6/Frequenz;
  Periodendauer_ms = round(konvert); //ms
  pinMode(pin,OUTPUT);
  Winkel(false);
  micros_alt = micros();
}

void servo::Winkel(bool offen) { // true = 90°+verstellwinkel/2°, false = 90°-verstellwinkel/2°

  uint16_t obere_grenze = ms_0_grad + (ms_180_grad-ms_0_grad)*((90+verstellwinkel/2)-0)/(180-0); // lineare Interpolation zw. 0° und 180° für 90°+verstellwinkel/2
  uint16_t untere_grenze = ms_0_grad + (ms_180_grad-ms_0_grad)*((90-verstellwinkel/2)-0)/(180-0); // lineare Interpolation zw. 0° und 180° für 90°-verstellwinkel/2

  if (offen) {
    Einschaltdauer = obere_grenze;
  } else {
    Einschaltdauer = untere_grenze;
  }
}

void servo::einstellen() { //Serial.begin() in setup
  if (Serial.available()) {
    delay(5);
    String input = "";
    while (Serial.available())
      input+=(char)Serial.read();

    Einschaltdauer = input.toInt();
  }
}

void servo::Halten() { // PWM
  if (micros()-micros_alt >= Periodendauer_ms) {// prüft ob eine Periode vergangen ist
    //PWM Signal 
    micros_alt = micros();
    digitalWrite(pin, HIGH);
    delayMicroseconds(Einschaltdauer);
    digitalWrite(pin, LOW);
  }
}
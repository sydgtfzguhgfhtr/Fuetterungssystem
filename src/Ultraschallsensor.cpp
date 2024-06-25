#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Ultraschallsensor.h"

Ultraschallsensor::Ultraschallsensor(uint8_t echo_pin, uint8_t trigger_pin) {
  echo = echo_pin;
  trig = trigger_pin;

  pinMode(trig,OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig,HIGH);
}


float Ultraschallsensor::messung(bool messen) {
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);

    uint16_t duration = pulseIn(echo,HIGH);
    float s_cm = duration*0.034/2;
    if (s_cm <= max_hoehe && messen) { // vermeidet Fehlmessungen
      messung_alt = s_cm;
      Serial.print("Messung: ");
      Serial.println(s_cm);
      return s_cm;
    } else 
      return messung_alt;
}
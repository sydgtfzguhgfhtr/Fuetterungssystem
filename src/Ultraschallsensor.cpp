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


float Ultraschallsensor::messung() {
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);

    uint16_t duration = pulseIn(echo,HIGH);
    float s_cm = duration*0.034/2;
    if (s_cm <= max_hoehe && messung_alt - s_cm <= max_unterschied) { // vermeidet Fehlmessungen
      messung_alt = s_cm;
      Serial.print("Messung: ");
      Serial.println(s_cm);
      fehler = 0;
      return s_cm;
    } else {
      fehler++;
      return -1;
    }
    if (fehler >= 20) {
      return -10;
    }

    //return -1: messfehler; erneut messen
    //return -10: 20 Messfehler; Messung abgebrochen
}

float Ultraschallsensor::fuellstand(float m) {
  // 0% = 50cm
  // 100% 0cm
  float fuellstand = 100-(m/50)*100;
  return fuellstand;
}
#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Ultraschallsensor.h"

ultraschallsensor::ultraschallsensor(uint8_t echo_pin, uint8_t trigger_pin) {
  echo = echo_pin;
  trig = trigger_pin;

  pinMode(trig,OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig,HIGH);
}

float ultraschallsensor::messung() {
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);

    uint16_t duration = pulseIn(echo,HIGH);
    float s_cm = duration*0.034/2;
    if ((messung_alt <= s_cm+2 || messung_alt >= s_cm-2) && s_cm <= max_hoehe) {
      messung_alt = s_cm;
      return s_cm;
    } else 
      return messung_alt;
}
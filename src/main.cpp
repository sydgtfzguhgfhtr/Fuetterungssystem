#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Zeit.h"
#include "Ultraschallsensor.h"
#include "Servo.h"

zeit Zeit;

void setup() {
}

void loop() {
  Zeit.vergangene_zeit();
}
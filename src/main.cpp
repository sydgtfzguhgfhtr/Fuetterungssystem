#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Zeit.h"

zeit Zeit;

void setup() {
}

void loop() {
  Zeit.vergangene_zeit();
}
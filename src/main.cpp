#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Zeit.h"
#include "Ultraschallsensor.h"
#include "Servo.h"

ultraschallsensor US(D5, D6);

void setup() {
  Serial.begin(115200);
}

void loop() {
  float strecke = US.messung();
  Serial.println(strecke);
  delay(100);
}

#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include <MQTT.h>
#include "Ultraschallsensor.h"
#include "Servo.h"

servo Servo(D9,50,true);
ultraschallsensor US(D6,D7);

void setup() {
}

void loop() {
  Servo.Winkel(true);
  Servo.Halten();
}
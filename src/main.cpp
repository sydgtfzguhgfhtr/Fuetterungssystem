#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include <MQTT.h>
#include "Ultraschallsensor.h"
#include "Servo.h"

servo Servo(D9,50,true);
ultraschallsensor US(D6,D7);
bool fuettern = false;
bool servo_auf = false;
bool messen = false;
uint64_t zeit_alt;
uint32_t fuetterzeit = 200;
uint16_t messzeit = 100;

void setup() {

}

void loop() {
  if (fuettern) {
    zeit_alt = millis();
    servo_auf = true;
    fuettern = false;
  }
  if ((millis() - zeit_alt >= fuetterzeit) && servo_auf) {
    servo_auf = false;
    zeit_alt = millis();
    messen = true;
  }
  if ((millis() - zeit_alt >= messzeit) && messen) {
    messen = false;
  }

  Servo.Winkel(servo_auf);
  Servo.Halten();
  US.messung(messen);
}
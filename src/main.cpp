#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Zeit.h"
#include "Ultraschallsensor.h"
#include "Servo.h"

zeit Zeit_zwischen_Fuetterung;
zeit Dauer_Fuetterung;
servo Servo(D9,50,true);

void setup() {
  pinMode(D9,OUTPUT);
}

void loop() {
  // Zeit_zwischen_Fuetterung.vergangene_zeit();
  // Dauer_Fuetterung.vergangene_zeit();
  Servo.Winkel(true);
  Servo.Halten();
}

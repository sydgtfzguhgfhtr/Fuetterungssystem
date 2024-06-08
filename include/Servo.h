#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  

class servo {
  private:
    uint8_t pin;
    float Frequenz; 
    uint64_t micros_alt;
    uint32_t Periodendauer_ms;
    uint32_t Einschaltdauer; // Einschaltdauer

    // Servoeinstellungen
    uint16_t ms_0_grad = 450; //PWM mikrosekunden für Winkel 0°
    uint16_t ms_180_grad = 2450; //PWM mikrosekunden für Winkel 180°
    uint8_t verstellwinkel = 60; //Verstellwinkel zum Öffnen der Lochscheibe
  
  public:
    servo(uint8_t PIN, float Frequenz, bool winkel);
    void Winkel(bool winkel);
    void einstellen();
    void Halten(); //PWM zum Halten des Servoverstellwinkels
};
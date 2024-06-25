#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  

class Servo {
  private:
    uint8_t pin;
    float Frequenz; 
    uint64_t micros_alt;
    uint32_t Periodendauer_ms;
    uint32_t Einschaltdauer; // Einschaltdauer
  
  public:	
    Servo(uint8_t PIN, float Frequenz, bool winkel);
    void Winkel(bool winkel);
    void einstellen();
    void Halten(); //PWM zum Halten des Servoverstellwinkels
};
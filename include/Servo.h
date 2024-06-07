#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  

class servo
{
  private:
    uint8_t pin;
    float Frequenz;
    uint64_t micros_alt;
    uint32_t Periodendauer_ms;
    uint32_t Einschaltdauer; // Einschaltdauer

  
  public:
    servo(uint8_t PIN, float Frequenz, bool in_Winkel);
    void Winkel(bool winkel);
    void Halten();
};
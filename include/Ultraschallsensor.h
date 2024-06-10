#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  

class ultraschallsensor {
    private:
        uint8_t echo;
        uint8_t trig;
        float messung_alt;
        float max_hoehe = 50;

    public:
        ultraschallsensor(uint8_t echo_pin, uint8_t trig_pin);
        float messung(bool messen);
};
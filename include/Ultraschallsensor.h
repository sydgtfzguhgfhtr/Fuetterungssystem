#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  

class Ultraschallsensor {
    private:
        uint8_t echo;
        uint8_t trig;
        float messung_alt;
        float max_hoehe = 50;
        float max_unterschied = 5;
        float fehler = 0;

    public:
        Ultraschallsensor(uint8_t echo_pin, uint8_t trig_pin);
        float messung();
        float fuellstand(float m);
};
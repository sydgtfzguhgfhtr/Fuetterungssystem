#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  

class zeit {
    private:
        unsigned long long alte_zeit;

    public:
        zeit();
        void vergangene_zeit();
        void zeit_zuruecksetzen();
        uint32_t sekunden = 0;
        uint32_t minuten = 0;
        uint32_t stunden = 0;
        uint32_t tage = 0;
        uint32_t wochen = 0;
};
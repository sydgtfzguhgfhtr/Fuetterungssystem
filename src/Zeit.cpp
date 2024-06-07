#include <stdio.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "Zeit.h"

zeit::zeit() {
    alte_zeit = millis();
    minuten = 0;
    stunden = 0;
    tage = 0;
    wochen = 0;
};

void zeit::vergangene_zeit() {
    if (millis() - alte_zeit >= 1000) {
        sekunden++;
        alte_zeit = millis();
        if (sekunden >= 60*(minuten+1)) {
            minuten++;
        }
        if (minuten >= 60*(stunden+1)) {
            stunden++;
        }
        if (stunden >= 24*(tage+1)) {
            tage++;
        }
        if (tage >= 7*(wochen+1)) {
            wochen++;
        }
    }
};

void zeit::zeit_zuruecksetzen() {
    alte_zeit = millis();
    minuten = 0;
    stunden = 0;
    tage = 0;
    wochen = 0;
}
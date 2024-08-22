#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include <MQTT.h>
#include "Ultraschallsensor.h"
#include "Servo.h"

Servo servo(D9,50,false);
Ultraschallsensor us(D6,D7);
bool fuettern = false;
bool servo_auf = false;
bool messen = false;
uint64_t zeit_alt;
uint32_t futtermenge = 5;
uint32_t gefuettert = futtermenge;
uint32_t fuetterzeit = 800;
uint16_t messzeit = 50;
float entf;
uint16_t fuellstand = 574;

const String topic_fuettern = "/Fuetterung/fuettern";
const String topic_menge = "/Fuetterung/menge_aendern";
const String topic_fuellstand_senden = "/Fuetterung_fuellstand";
const String topic_auffuellen = "/Fuetterung_Futter_auffuellen";

const char ssid[] = "Galaxy A52";
const char pass[] = "xxxxxxxxx";
WiFiClient net;
MQTTClient client;
uint64_t alte_zeit_mqtt = millis();

void connect();
void messageReceived(String &topic, String &payload);
void fuetterung();


void setup() {
  servo.Winkel(false);
  Serial.begin(115200);
  WiFi.begin(ssid,pass);

  client.begin("94.130.103.21",net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  fuetterung();
}

//Funktionen:

void fuetterung() {
  servo.Halten();
  servo.Winkel(servo_auf);

  if (millis() - alte_zeit_mqtt >= 50) {
    client.loop();
    alte_zeit_mqtt = millis();
    if (!client.connected()) {
      Serial.println(String(client.connected()));
      connect();
    }
  }
  if (fuettern) {
      zeit_alt = millis();
      servo_auf = true;
      fuettern = false;
    }
  if ((millis() - zeit_alt >= fuetterzeit * 2) && servo_auf) {
      servo_auf = false;
      zeit_alt = millis();
  }
  if (!servo_auf && gefuettert <= futtermenge && (millis() - zeit_alt >= fuetterzeit)) {
    zeit_alt = millis();
    servo_auf = true;
    gefuettert++;
    zeit_alt = millis();
  }
}



void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if (topic == topic_fuettern) {
    fuettern = true;
    gefuettert = 2;
    Serial.println("Fuettern");
    fuellstand -= futtermenge;
    client.publish(topic_fuellstand_senden, String(fuellstand*11));
  }
  if (topic == topic_menge) {
    uint16_t futtermenge_ein = payload.toInt();
    futtermenge = futtermenge_ein / 11;
    gefuettert = futtermenge+1;
    Serial.print("menge:");
    Serial.println(futtermenge);
  }
  if (topic == topic_auffuellen) {
    fuellstand = 574;
  }
}

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting..");
  while (!client.connect("cdgfrtzhctrlhsn","mosquitto","MqttHSA!1#")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnected!");
  client.subscribe("/Fuetterung/menge_aendern");
  client.subscribe("/Fuetterung/fuettern");
  Serial.println("erfolgreich");
}
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
uint32_t futtermenge = 100;
uint32_t fuetterzeit = 2000;
uint16_t messzeit = 50;

const String topic_fuettern = "/Fuetterung/fuettern";
const String topic_auf = "/Fuetterung/auf";
const String topic_zu = "/Fuetterung/zu";
const String topic_menge = "/Fuetterung/menge_aendern";
const String topic_fuellstand_senden = "/Fuetterung_fuellstand";

const char ssid[] = "Galaxy A52s 5G0AE6";
const char pass[] = "---------";
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
  if ((millis() - zeit_alt >= fuetterzeit) && servo_auf) {
    servo_auf = false;
    zeit_alt = millis();
    messen = true;
  }
  if ((millis() - zeit_alt >= messzeit) && messen) {
    messen = false;
  }

  servo.Winkel(servo_auf);
  servo.Halten();
  // us.messung(messen);
}



void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if (topic == topic_fuettern) {
    fuettern = true;
    Serial.println("Fuettern");
  }
  if (topic == topic_menge) {
    futtermenge = payload.toInt();
    fuetterzeit = futtermenge;
    Serial.print("menge:");
    Serial.println(futtermenge);
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
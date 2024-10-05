#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define WIFI_NETWORK "NSA_Connection_Pool"
#define WIFI_PASSWORD "..."
#define WIFI_TIMEOUT_MS 15000

#define DHTPIN 26
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

int temperature = 0;

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS) {
    Serial.println("...");
    delay(200);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed!");
    return;
  }

  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  dht.begin();

  connectToWiFi();
}

void loop() {
  temperature = dht.readTemperature();

  HTTPClient http;

  // Prepare JSON document
  DynamicJsonDocument doc(2048);
  doc["temperature"] = temperature;

  // Serialize JSON document
  String json;
  serializeJson(doc, json);

  http.begin("http://4.180.5.111:3000/temperature");
  http.addHeader("Content-Type", "application/json");
  http.POST(json);

  http.end();

  delay(800);

  temperature = (temperature + 1) % 100;
}

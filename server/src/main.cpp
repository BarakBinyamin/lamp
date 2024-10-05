#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define TOPIC "arduino"

const int ledPin = 2;

// Replace these with your Wi-Fi and MQTT broker settings
const char* ssid = "It Burns When IP";
const char* password = "washington";
const char* mqtt_server = "73.234.162.86";  // Replace with your MQTT broker address (e.g., test.mosquitto.org)

WiFiClient espClient;
PubSubClient client(espClient);

int state;

// Function to handle incoming MQTT messages
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  state = !state;
  Serial.printf("State changed to: %d\n", state);
  digitalWrite(ledPin, state);
}

// Function to reconnect to MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {  // Client ID for MQTT broker
      Serial.println("connected");
      client.subscribe(TOPIC);
    } else {
      Serial.print("failed, rc=");
      // Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, 8001);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

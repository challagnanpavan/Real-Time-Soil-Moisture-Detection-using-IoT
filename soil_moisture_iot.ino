#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "DENNY";
const char* password = "doreman@007";


// ThingSpeak API credentials
const char* thingspeak_api_key = "VCSE0S9WJ0WYQMQ4";
const char* thingspeak_channel_id = "2926165";

const int soil_moisture_pin = A0;  // Analog pin for soil moisture sensor

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Initializing...");
}

void loop() {
  int soil_moisture_value = analogRead(soil_moisture_pin);
  Serial.print("Soil Moisture: ");
  Serial.println(soil_moisture_value);

  // Send data to ThingSpeak
  if (client.connect("api.thingspeak.com", 80)) {
    String post_data = "field1=" + String(soil_moisture_value);
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + String(thingspeak_api_key) + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(post_data.length());
    client.print("\n\n");
    client.print(post_data);
    delay(15000);  // ThingSpeak free account limit
  }
  client.stop();
  delay(10000);  // Adjust according to your needs
}

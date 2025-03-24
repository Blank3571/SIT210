#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include <DHT.h>
#include "secrets.h"  // Include WiFi and API credentials

// Pin Definitions
#define DHTPIN 2        // Data pin for DHT sensor
#define DHTTYPE DHT11   // Use DHT11

// Initialize objects
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

// ThingSpeak Channel ID
unsigned long myChannelNumber = 2888773; 

void setup() {
    Serial.begin(115200);
    dht.begin();

    // Connect to WiFi
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("Connected!");

    // Initialize ThingSpeak
    ThingSpeak.begin(client);
}

void loop() {
    // Read temperature and humidity
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check if readings are valid
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        delay(1000);
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C | Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    // Send data to ThingSpeak
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    
    int response = ThingSpeak.writeFields(myChannelNumber, SECRET_APIKEY);
    
    if (response == 200) {
        Serial.println("Data sent to ThingSpeak successfully!");
    } else {
        Serial.print("Error sending data, code: ");
        Serial.println(response);
    }

    // Wait 60 seconds before next reading
    delay(60000);
}

#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

const char* ssid = "Blank";        // Wi-Fi SSID
const char* password = "Gameboy3571"; //  Wi-Fi password

char ifttt_host[] = "maker.ifttt.com";  // IFTTT Webhook server (only the domain)
String ifttt_key = "cjRc-WPobNrzUzIF3sGG9T";  // IFTTT Webhooks key

WiFiSSLClient wifi;  // Use SSL client for HTTPS
HttpClient client = HttpClient(wifi, ifttt_host, 443);  // Use port 443 for HTTPS

const int lightSensorPin = A0;   // Light sensor connected to Analog Pin A0
const int threshold = 250;       // threshold based on ambient light levels
bool sunlightDetected = false;   // Track sunlight state

void sendIFTTTTrigger(String event = "sunlight_detected") {
    String requestURL = "/trigger/" + event + "/with/key/" + ifttt_key;
    
    Serial.print("Sending request to: ");
    Serial.println(requestURL);

    client.beginRequest();
    client.get(requestURL);
    client.sendHeader("Host", "maker.ifttt.com");
    client.sendHeader("Connection", "close");
    client.endRequest();

    // Read response from server
    Serial.println("Waiting for response...");
    while (client.available()) {
        char c = client.read();
        Serial.print(c);
    }

    Serial.println("\nIFTTT Trigger Sent!");
}

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
}

void loop() {
    int lightLevel = analogRead(lightSensorPin);
    Serial.print("Light Level: ");
    Serial.println(lightLevel);

    if (lightLevel > threshold && !sunlightDetected) {
        Serial.println("Sunlight detected! Sending IFTTT trigger...");
        sendIFTTTTrigger();
        sunlightDetected = true;
    }
    else if (lightLevel <= threshold && sunlightDetected) {
        Serial.println("Sunlight gone! Sending IFTTT trigger...");
        sendIFTTTTrigger("sunlight_stopped");
        sunlightDetected = false;
    }

    delay(5000);  // Check every 5 seconds
}

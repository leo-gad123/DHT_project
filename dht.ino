/*
developer name: leogad
date: 17/05/2015
description: "This code help to send data from dht sensor to be displayed by using Firebase real
time database on web
tip: Enjoy this code
*/




#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

#define DHTPIN D2      // DHT11 connected to GPIO2 (D4 on NodeMCU)
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// WiFi Credentials
const char* ssid = "EdNet";// you can put your own network
const char* password = "Huawei@123";

// Firebase Credentials
#define FIREBASE_HOST "dht-11-77602-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "wixne0qPzTkRNkGlOMo026r1Fb65ir0rsNGVp8X3"

FirebaseData fbData;
FirebaseConfig config;
FirebaseAuth auth;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected to WiFi");

    // Set Firebase Config
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    dht.begin();
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    // Send data to Firebase (use fbData object directly)
    if (Firebase.setFloat(fbData, "/DHT11/Temperature", temperature)) {
        Serial.println("Temperature Sent to Firebase");
    } else {
        Serial.println("Failed to send temperature");
        Serial.println(fbData.errorReason());
    }

    if (Firebase.setFloat(fbData, "/DHT11/Humidity", humidity)) {
        Serial.println("Humidity Sent to Firebase");
    } else {
        Serial.println("Failed to send humidity");
        Serial.println(fbData.errorReason());
    }

    delay(5000); // Wait for 5 seconds before next reading
}

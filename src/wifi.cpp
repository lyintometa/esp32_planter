#include <Arduino.h>
#include <WiFi.h>         //Wifi
#include <NTPClient.h>    //Time
#include <WiFiUdp.h>
#include <U8g2lib.h>      //Display
#include <DHT.h>          //Hygrometer

#include <bitmaps.h>
#include <functions.h>

// WiFi Variables
const char *ssid     = "Du kommst hier nicht rein";
const char *password = "ichkenndentuersteher";

const int timeBetweenAttempts = 10; // seconds
int previousAttemtTime = 0;

// Initialize WiFi
void WiFiInit(int timeOut) {
    Serial.println("WiFI init");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED && timeOut){
        timeOut = timeOut - 1;
        delay(1000);
    }
    if (WiFi.status() == WL_CONNECTED){
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        updateSystemTime();
    }
    return;
}

// Reconnect or Initialize WiFi
void WiFiReconnect() {
    if (WiFi.status() == WL_CONNECTED) return;
    Serial.println("WiFI reconnect");
    if (millis() <= previousAttemtTime + (timeBetweenAttempts * 1000)) return;
    previousAttemtTime = millis();
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_STA);
    delay(200);
    WiFiInit(2);
    return;
}

// Implement Soft Access Point for connecting to a new network
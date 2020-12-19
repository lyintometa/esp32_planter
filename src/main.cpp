#include <Arduino.h>
#include <WiFi.h>         //Wifi
#include <NTPClient.h>    //Time
#include <WiFiUdp.h>
#include <U8g2lib.h>      //Display
#include <DHT.h>          //Hygrometer

#include <bitmaps.h>
#include <functions.h>

void setup() {
  Serial.begin(9600);
  Serial.println("------Init------");
  displayInit();
  WiFiInit(4);
  DHTInit();
  LEDInit();
}

void loop() {
  Serial.println("------Loop------");
  WiFiReconnect();
  displayUpdate();
  //ledcWrite(0, 255);
  LEDUpdate();
  delay(200);
}

// Serial prints

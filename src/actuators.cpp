#include <Arduino.h>
#include <WiFi.h>         //Wifi
#include <NTPClient.h>    //Time
#include <WiFiUdp.h>
#include <U8g2lib.h>      //Display
#include <DHT.h>          //Hygrometer

#include <bitmaps.h>
#include <functions.h>

//LEDs
int pinLED = 16;
const int freq = 20000;
const int ledChannel = 0;
const int res = 8;
int brightness = 0; // 0 to 255

int turnOnTimeWeekday = 8 * 60 + 00;   // hour * 60 + minute
int turnOffTimeWeekday = 22 * 60 + 00; // hour * 60 + minute

int turnOnTimeWeekend = 10 * 60 + 00;   // hour * 60 + minute
int turnOffTimeWeekend = 24 * 60 + 00; // hour * 60 + minute

int transitionTime = 30;        // minutes

//Pump
int pinPump = 18;


// LED PWM config
void LEDInit(){
  ledcSetup(ledChannel, freq, res);
  ledcAttachPin(pinLED, ledChannel);
}

// Updates the LEDs with the correct brightness
void LEDUpdate() {
    Serial.println("LEDUpdate");
    brightness = determineBrightness();
    Serial.println("LEDUpdate2");
    Serial.println(brightness);
    delay(2000);
    ledcWrite(ledChannel, brightness);
    Serial.println("LEDUpdate3");
    return;
}

// Determines the brightess depending on the time
int determineBrightness() {
    Serial.println("determineBrightness");
    float value;
    float fTurnOnTime = getTurnOnToday() * 60;
    float fTurnOffTime = getTurnOffToday() * 60;
    float fCurrentTime = getTimeSeconds();  
    Serial.println("determineBrightness3");
    float fTransitionTime = transitionTime * 60;

    if ((fCurrentTime <= fTurnOnTime) | (fCurrentTime >= fTurnOffTime)){
        return 0;
    } 
    else if (fCurrentTime <= (fTurnOnTime + fTransitionTime)){
        value = ((fCurrentTime - fTurnOnTime)/fTransitionTime)*(PI/2);
        return sin(value) * 255;
    } 
    else if (fCurrentTime >= (fTurnOffTime - fTransitionTime)){
        value = ((fTurnOffTime - fCurrentTime)/fTransitionTime)*(PI/2);
        return sin(value) * 255;
    } 
    else {
        return 255;
    }
}

// Returns the time the LED should begin to turn on
int getTurnOnToday(){
    Serial.println("getTurnOnToday");
    int day = getWeekday();
    if ((day == 0) | (day == 6)) return turnOnTimeWeekend;
    return turnOnTimeWeekday;
}

// Returns the time the LED should be completly off
int getTurnOffToday(){
    Serial.println("getTurnOffToday");
    int day = getWeekday();
    if ((day == 5) | (day == 6)) return turnOffTimeWeekend;
    return turnOffTimeWeekday;
}
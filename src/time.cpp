#include <Arduino.h>
#include <WiFi.h>         //Wifi
#include <NTPClient.h>    //Time
#include <WiFiUdp.h>
#include <U8g2lib.h>      //Display
#include <DHT.h>          //Hygrometer

#include <bitmaps.h>
#include <functions.h>

// Time variables
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600);
bool timeUpdated = false;

// Updates the timeClient only when WiFi is connected and the current Time is not up to date
void updateSystemTime() {
    if (WiFi.status() != WL_CONNECTED) return;
    Serial.print("Updating system time: ");
    timeUpdated = true;
    timeClient.update();
    Serial.println(timeClient.getFormattedTime());
    return;
}

// Returns the current Time in minutes from midnight
int getTimeMinutes() {
    int minutes = 60 * timeClient.getHours();
    minutes = minutes + timeClient.getMinutes();
    return minutes;
}

// Returns the current Time in seconds from midnight
int getTimeSeconds() {
    int seconds = 3600 * timeClient.getHours();
    seconds = seconds + 60 * timeClient.getMinutes();
    seconds = seconds + timeClient.getSeconds();
    return seconds;
}

// Returns the weekDay
int getWeekday() {
    return timeClient.getDay();
}

// Returns the state of the time
bool isTimeUpdated(){
    return timeUpdated;
}
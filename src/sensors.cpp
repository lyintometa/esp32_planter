#include <Arduino.h>
#include <WiFi.h>         //Wifi
#include <NTPClient.h>    //Time
#include <WiFiUdp.h>
#include <U8g2lib.h>      //Display
#include <DHT.h>          //Hygrometer

#include <bitmaps.h>
#include <functions.h>

//Hygrometers
const int countDHT = 1;
const int pinsDHT[countDHT] = {0}; // 13
DHT *myDHTs[countDHT];

//Soil humidity sensors
const int countSMS = 2;
int pinsSMS[countSMS] = {0, 0}; // 12, 27

//Water level sensors
const int countWLS = 1;
int pinsWLS[countWLS] = {0}; // 33

// Initializes the hyrometers
void DHTInit() {
    for (int i = 0; i < countDHT; i++) {
        myDHTs[i] = new DHT(pinsDHT[i], DHT11);
        myDHTs[i]->begin();
    }
}

// Returns the average of the temperatures of the DHT sensor(s)
float readTemperatureSensors() {
    Serial.print("Reading temperature sensors: ");
    float temperatures[countDHT] = {0};
    for (int i = 0; i < countDHT; i++) {
        temperatures[i] =  myDHTs[i]->readTemperature();
    }
    int result = avgNotZero(temperatures, countDHT);
    Serial.println(result);
    return result;
}

// Returns the average of the humidities of the DHT sensor(s)
int readHumiditySensors() {
    Serial.print("Reading humidity sensors: ");
    float humidities[countDHT] = {0};
    for (int i = 0; i < countDHT; i++) {
        humidities[i] =  myDHTs[i]->readHumidity();
    }
    int result = avgNotZero(humidities, countDHT);
    Serial.println(result);
    return result;
}

// Return the average of the water level sensor(s)
int readWaterLevelSensors() {
    float values[countWLS] = {0};
    for (int i = 0; i < countWLS; i++){
        if (pinsWLS[i]) {
            values[i] = analogRead(pinsWLS[i]);
        }
    }
    return avgNotZero(values, countWLS);
}

// Return the average of the water level sensor(s)
int readSoilMoistureSensors() {
    float values[countSMS] = {0};
    for (int i = 0; i < countSMS; i++){
        if (pinsSMS[i]) {
            values[i] = analogRead(pinsSMS[i]);
        }
    }
    return avgNotZero(values, countSMS);
}

// Returns the avarage of an array, not counting 0-values
float avgNotZero(float *arr, int size) {
    int numElements = 0; // num of notzero elements
    float sum = 0;
    for (int i = 0; i < size; i++) {
        if (!isnan(arr[i])) {
        numElements++;
        sum = sum + arr[i];
        }
    }
    if (numElements == 0) return 0;
    return sum/numElements;
}
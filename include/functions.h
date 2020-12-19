#ifndef FUNCTION_PROTOTYPE_H
#define FUNCTION_PROTOTYPE_H

// display
void displayInit();
void displayUpdate();

void drawStartScreen();
void drawWiFi();
void drawCurTime();
void drawWeekday();
void drawTemperature();
void drawHumidity();
void drawWaterLevel();
void drawSoilMoisture();

// WiFi
void WiFiInit(int timeOut);
void WiFiReconnect();

// Time
void updateSystemTime();
int getTimeMinutes();
int getTimeSeconds();
int getWeekday();
bool isTimeUpdated();

// Sensors
void DHTInit();
float readTemperatureSensors();
int readHumiditySensors();
int readSoilMoistureSensors();
int readWaterLevelSensors();
float avgNotZero(float *arr, int size);

// Actuators
void LEDInit();
void LEDUpdate();
int determineBrightness();
int getTurnOnToday();
int getTurnOffToday();

#endif
#include <Arduino.h>
#include <WiFi.h>         //Wifi
#include <NTPClient.h>    //Time
#include <WiFiUdp.h>
#include <U8g2lib.h>      //Display
#include <DHT.h>          //Hygrometer

#include <bitmaps.h>
#include <functions.h>

// Display variables
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
u8g2_uint_t width;

// Initialization
void displayInit() {
    u8g2.begin();
    u8g2.setFont(u8g2_font_lubR08_tf);
    u8g2.setFontMode(0);
    drawStartScreen();
    return;
}

// Updates the display with new values
void displayUpdate() {
    u8g2.firstPage();
    drawWiFi();
    drawCurTime();
    drawWeekday();

    drawTemperature();
    drawHumidity();
    u8g2.nextPage();
    return;
}

// Draws the Start screen (for loading WiFi in background)
void drawStartScreen() {
    u8g2.firstPage();
    u8g2.drawXBMP(40, 20, 48, 22, logo_bits);
    u8g2.nextPage();
    return;
}

// Draws the status of the Wifi
void drawWiFi() {
    if (WiFi.status() == WL_CONNECTED){
        u8g2.drawXBMP( 116, 6, 8, 8, wifi2_bits);
    } else {
        u8g2.drawXBMP(116, 6, 8, 8, wifi0_bits);
    }
    return;
}

// Draws the current time
void drawCurTime() {
    if (!isTimeUpdated()) return;
    int time = getTimeMinutes();
    int hour = time / 60;
    int minute = time % 60;
    char hour0 = hour / 10 + 48;
    char hour1 = hour % 10 + 48;
    char minute0 = minute / 10 + 48;
    char minute1 = minute % 10 + 48;
    char curTime[6] = {hour0 , hour1, 58, minute0, minute1};
    u8g2_uint_t offsetAlignRight = 128 - 16 - u8g2.getUTF8Width(curTime); // = Screensize - offsetright - width
    u8g2.drawUTF8(offsetAlignRight, 14, curTime);
    return;
}
/* 
void drawLEDTime(int x, int y, int time){
    int hour = time / 60;
    int minute = time % 60;
    char drawTime[6] = {(hour / 10) + 48, (hour % 10) + 48, 58, (minute / 10) + 48, (minute % 10)};
} */

void drawWeekday(){
    if (!isTimeUpdated()) return;
    String weekDays[7]={"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
    String weekDayStr = weekDays[getWeekday()];
    char weekday[3];
    weekDayStr.toCharArray(weekday, 3);
    u8g2_uint_t offsetAlignRight = 128 - 34 - 16 - u8g2.getUTF8Width(weekday); // = Screensize - offsetright - width
    u8g2.drawUTF8(offsetAlignRight, 14, weekday);
    return;
}

// Prints the temperature in °C at the screen coordinates
void drawTemperature() {
    float temperature = readTemperatureSensors();
    u8g2.setCursor(64, 30);
    if (temperature) u8g2.print(temperature, 1);
    u8g2.drawUTF8(26, 30, "°C");
    return;
}
// Prints the humidity in % at the screen coordinates
void drawHumidity() {
    float humidity = readHumiditySensors();
    u8g2.setCursor(64, 30);
    if (humidity) u8g2.print(humidity, 0);
    u8g2.drawUTF8(78, 30, "%");
    return;
}

// Draw water tank
void drawWaterLevel() {    
    int waterLevel = readWaterLevelSensors();
    char watChar[10];
    dtostrf(waterLevel, 4, 0, watChar);
    u8g2_uint_t offsetAlignRight = 128 - 4 - u8g2.getUTF8Width(watChar); // = Screensize - offsetright - width
    u8g2.drawUTF8(offsetAlignRight, 53, watChar);
    return;
}

// Draw moisture display
void drawSoilMoisture() {
    int soilMoisture = readSoilMoistureSensors();
    char watChar[10];
    dtostrf(soilMoisture, 4, 0, watChar);
    u8g2_uint_t offsetAlignRight = 128 - 4 - u8g2.getUTF8Width(watChar); // = Screensize - offsetright - width
    u8g2.drawUTF8(offsetAlignRight, 53, watChar);
    return;
}
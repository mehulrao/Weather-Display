#include <Arduino.h>
#include <LiquidCrystal.h>
#include <dht.h>
#include <string.h>
#include <RTClib.h>
#include <Wire.h>

dht DHT;
RTC_DS3231 RTC;

#define DHT11_PIN 7
int potPin = 2;
int val = 0;
String temp = "  ";
String hum = "     ";
String tempold = "  ";
String humold = "     ";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
    Serial.begin(9600);
    if (!RTC.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1)
            ;
    }
    //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    lcd.begin(16, 2);
    lcd.display();
}

void loop() {
    int chk = DHT.read11(DHT11_PIN);
    temp = (int)round(1.8 * DHT.temperature + 32);
    hum = DHT.humidity;
    Serial.print("TempOld: ");
    Serial.println(tempold);
    Serial.print("Temp: ");
    Serial.println(temp);
    Serial.print("HumOld: ");
    Serial.println(humold);
    Serial.print("Hum: ");
    Serial.println(hum);
    if (tempold == temp) {
        if (humold == hum) {
            lcd.noCursor();
            Serial.println("ENTERED RELOOP   ");
            Serial.println("");
            delay(2000);
            return;
        }
    }
    Serial.println("NEW INFO");
    Serial.println("");
    //lcd.noDisplay();
    //delay(200);
    //lcd.display();
    lcd.clear();
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("T: ");
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("F");
    lcd.setCursor(9, 0);
    String humStr = String(hum);
    int lhum = humStr.lastIndexOf(".");
    humStr.remove(lhum);
    lcd.print("H: ");
    lcd.print(humStr);
    lcd.print((char)37);
    lcd.setCursor(0, 1);
    lcd.print("    ");
    DateTime now = RTC.now();
    lcd.print(now.hour());
    lcd.print(":");
    lcd.print(now.minute());
    lcd.print(":");
    lcd.print(now.second());
    tempold = temp;
    humold = hum;
    delay(2000);
}

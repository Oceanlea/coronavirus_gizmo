//Author: Andrew Adiletta
//Date: Jan 27. 2020
//About
/*
The following is a simple Webscraper that gets the number of cases of 
Coronavirus found worldwide. Originally, I had planned on the Esp8266 
doing the scraping from the Chinese servers, but I realized this was too 
difficult, so I set up a cheap computer runnning linux to do the scraping
*/

//Include libraries
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

 ESP8266WiFiMulti WiFiMulti;
long prevNum = 0;
 void setup() {

   Serial.begin(115200);
   // Serial.setDebugOutput(true);

   Serial.println();
   Serial.println();
   Serial.println();

   //Clean up Serial
   for (uint8_t t = 4; t > 0; t--) {
     Serial.printf("[SETUP] WAIT %d...\n", t);
     Serial.flush();
     delay(1000);
   }

   //Setup wifi
   WiFi.mode(WIFI_STA);
   WiFiMulti.addAP("SSID", "Password");
   lcd.init();                      // initialize the lcd
   // Print a message to the LCD.
   lcd.backlight();
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("CORONA VIRUS COUNTER");
   lcd.setCursor(4,2);
   lcd.print("Cases: 2070");
 }

 void loop() {


   // wait for WiFi connection
   if ((WiFiMulti.run() == WL_CONNECTED)) {

     WiFiClient client;

     HTTPClient http;

     Serial.print("[HTTP] begin...\n");
     if (http.begin(client, "http://serverIP:Port")) {  // HTTP


       Serial.print("[HTTP] GET...\n");
       // start connect
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


 #include <Arduino.h>

 #include <ESP8266WiFi.h>
 #include <ESP8266WiFiMulti.h>

 #include <ESP8266HTTPClient.h>

 #include <WiFiClient.h>

 ESP8266WiFiMulti WiFiMulti;
long prevNum = 0;
 void setup() {

   Serial.begin(115200);
   // Serial.setDebugOutput(true);

   Serial.println();
   Serial.println();
   Serial.println();

   for (uint8_t t = 4; t > 0; t--) {
     Serial.printf("[SETUP] WAIT %d...\n", t);
     Serial.flush();
     delay(1000);
   }

   WiFi.mode(WIFI_STA);
   //Replace with your own information
   WiFiMulti.addAP("SSID", "Password");
   lcd.init();                      // initialize the lcd
   // Print a message to the LCD.
   lcd.backlight();
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("CORONA VIRUS COUNTER");
   lcd.setCursor(4,2);
   lcd.print("Cases: 2070");
 }

 void loop() {


   // wait for WiFi connection
   if ((WiFiMulti.run() == WL_CONNECTED)) {

     WiFiClient client;

     HTTPClient http;

     Serial.print("[HTTP] begin...\n");
     //Replace with your own information
     if (http.begin(client, "http://Local_Server_IP:Port")) {  // HTTP

ion and send HTTP header
       int httpCode = http.GET();

       // httpCode will be negative on error
       if (httpCode > 0) {
         // HTTP header has been send and Server response header has been handled
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);

         // file found at server
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
           String payload = http.getString();
           String out = "Cases: ";
           payload.trim();

           out += payload;
           if(prevNum != payload.toInt()){
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("CORONA VIRUS COUNTER");
             lcd.setCursor(4,2);
             lcd.print(out);
             prevNum = payload.toInt();
           }
           Serial.println(out);
         }
       } else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
       }

       http.end();
     } else {
       Serial.printf("[HTTP} Unable to connect\n");
     }
   }

   delay(10000);
 }

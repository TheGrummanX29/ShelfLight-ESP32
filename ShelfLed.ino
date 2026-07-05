#define WIFI_SSID "" //type here your WiFi SSid
#define WIFI_PASS "" //type here your WiFi password
#define BOT_TOKEN "" //type here your Telegram bot token

#include <FastBot.h>
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> 
#endif

#define PIN        21 
#define NUMPIXELS 19 //type here your count of pixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500

#include <Wire.h>

FastBot bot(BOT_TOKEN);

void setup() {
  connectWiFi();
  bot.attach(newMsg);
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void newMsg(FB_msg& msg) {
  Serial.print(msg.chatID);
  Serial.print(", ");
  Serial.print(msg.username);
  Serial.print(", ");
  Serial.println(msg.text); 
  if (msg.text == "/say_hello") bot.sendMessage("Hello!", msg.chatID);
  if (msg.text == "/off")
  {
  bot.sendMessage("Backlight off!", msg.chatID);
  pixels.clear();
  pixels.show();
  }
  if (msg.text == "/white")
{
  bot.sendMessage("Current color: white", msg.chatID);
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
}

pixels.show();
delay(DELAYVAL);
}
 if (msg.text == "/red")
{
  bot.sendMessage("Current color: red", msg.chatID);
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
}

pixels.show();
delay(DELAYVAL);
}
 if (msg.text == "/aqua")
{
  bot.sendMessage("Current color: aqua", msg.chatID);
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 255));
}

pixels.show();
delay(DELAYVAL);
}
 if (msg.text == "/purple")
{
  bot.sendMessage("Current color: purple", msg.chatID);
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(128, 0, 128));
}

pixels.show();
delay(DELAYVAL);
}
}

void loop() {
  bot.tick();
  pixels.clear();
}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}

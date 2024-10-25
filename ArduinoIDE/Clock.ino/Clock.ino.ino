#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Clock";
IPAddress apIP(192, 168, 1, 1);
ESP8266WebServer server(80);
const int rs = D0, en = D1, d4 = D2, d5 = D3, d6 = D4, d7 = D5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  WiFi.softAP(ssid);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  lcd.begin(16, 1);
  lcd.setCursor(0, 0);
  lcd.print("1234567891234567");
  lcd.setCursor(0, 1);
  lcd.print("1234567890123456");
}

void loop() {

}

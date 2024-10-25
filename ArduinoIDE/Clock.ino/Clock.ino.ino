#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Clock";
IPAddress apIP(192, 168, 1, 1);
ESP8266WebServer server(80);

void setup() {
  WiFi.softAP(ssid);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
}

void loop() {
  // put your main code here, to run repeatedly:

}

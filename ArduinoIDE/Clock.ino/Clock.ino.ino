#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int Hour = 1;
int Min = 1;
int Sec = 1;
int old_Hour;
String am_pm = "AM";
String c;

int date = 1;
int month_num = 1;
int old_month;
int daysInMonth = 31;
int year = 2010;
int day_num = 1;
String day = "Mon";
String monthName = "Jan";
String d;

bool alarm_ = false;
bool buzz = false;
int alarm_H = 0;
int alarm_M = 0;
String alarm_ampm = "AM";
int alarm_time = 20;
int current_duration = 1;

unsigned long previousMillis = 0;
const long interval = 1000;

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

  server.on("/", HTTP_GET, handleTime);
  server.on("/updateDate", HTTP_GET, handleDate);
  server.on("/updateAlarm", HTTP_GET, handleAlarm);
  server.on("/alarm_off", HTTP_GET, AlarmOff);
  server.on("/setTime", HTTP_POST, handleSetTime);
  server.on("/setDate", HTTP_POST, handleSetDate);
  server.on("/setAlarm", HTTP_POST, handleSetAlarm);

  server.begin();
}

void loop() {
}

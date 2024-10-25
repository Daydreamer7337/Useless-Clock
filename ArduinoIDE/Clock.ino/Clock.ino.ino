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
int display_control = 0;

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
  int conv_Hour = 1;
  String CheckChange;
  String CheckChange_date;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Sec += 1;
    display_control += 1;
    if (Sec >= 60) {
      Sec = 0;
      Min += 1;
    }

    if (Min >= 60) {
      Min = 0;
      old_Hour = Hour;
      Hour += 1;
    }

    if (Hour >= 24) {
      Hour = 0;
      am_pm = "AM";
    }

    if(Hour >= 12){
      am_pm = "PM";
    }

    if(Hour > 12){
      conv_Hour = Hour - 12;
    }
    else{
      conv_Hour = Hour;
    }

    if(Hour != old_Hour){
        if(Hour == 0){
          date += 1;
          day_num += 1;
          fetchDayName();
        }
    }
    if(date > daysInMonth){
      date = 1;
      month_num += 1;
      fetchDaysInMonth();
      fetchMonthName();
    }
    if(month_num > 12){
      month_num = 1;
      year += 1;
    }

    CheckChange = c;
    c = "    ";
    c += conv_Hour;
    c += ":";
    c += Min;
    c += " ";
    c += am_pm;

    CheckChange_date = d;
    d = day;
    d += ", ";
    d += date;
    d += "-";
    d += monthName;
    d += "-";
    d += year;

    if(c != CheckChange || d != CheckChange_date){
      if(display_control <= 3){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(c);
      }
      else if(display_control <= 6){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(d);
      }
    }
    if(display_control > 6){
      display_control = 0;
    }
  }
}

void AlarmOff(){
  alarm_ = false;
  current_duration = 1;
  digitalWrite(D6, LOW);
  String disabledAlarm = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg, rgba(96,63,131,1) 0%, rgba(199,211,212,1) 1%, rgba(199,211,212,1) 99%, rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.SubmitBtn{margin-top:50px;margin-left:25%;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;} .navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);} #Txt{margin-top:50%;text-align:center;color:rgba(23, 5, 5, 0.771);} .SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23, 5, 5, 0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);color:lavender;}.InputTable{margin:auto;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>TURN OFF ALARM</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateDate'>DATE</a></li><li><a href='/updateAlarm'>ALARM</a></li></ul></div></div><div class='content'><table class='InputTable'><tr><td><h1 id='Txt'>ALARM HAS BEEN TURNED OFF<br>HAVE A NICE DAY</h1></td></tr></table></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
  server.send(200, "text/html", disabledAlarm);
}

void handleTime() {
  String time_site = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg,rgba(96,63,131,1) 0%,rgba(199,211,212,1) 1%,rgba(199,211,212,1) 99%,rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.InputTable{margin:auto;}.TextBox{margin-top:50px;height:50px;width:100%;border-radius:25px;border:2px solid #009688;text-align:center;}.SubmitBtn{margin-top:50px;margin-left:25%;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;}.navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);}.SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23,5,5,0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);color:lavender;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>Adjust Time</h1></div><div class='title'><div class='navbar'><ul><li><a href='/updateAlarm'>ALARM</a></li><li><a href='/updateDate'>DATE</a></li></ul></div></div><div class='content'><form action='/setTime' method='post'><table class='InputTable'><tr><td><input class='TextBox' type='text' id='Hour' name='Hour' placeholder='Enter Hours(in 24 Hrs).'></td></tr><tr><td><input class='TextBox' type='text' id='Min' name='Min' placeholder='Enter Minutes.'></td></tr><tr><td><input class='TextBox' type='text' id='Sec' name='Sec' placeholder='Enter Seconds.'></td></tr><tr><td><input class='SubmitButton' type='submit' value='Update'></td></tr></table></form></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
  server.send(200 , "text/html" , time_site);
}

void handleDate(){
  String date_site = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg,rgba(96,63,131,1) 0%,rgba(199,211,212,1) 1%,rgba(199,211,212,1) 99%,rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.InputTable{margin:auto;text-align:center;}.TextBox{margin-top:50px;height:50px;width:100%;border-radius:25px;border:2px solid #009688;text-align:center;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;}.navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);}#selectionBox{margin-top:50px;height:50px;width:100%;border-radius:25px;border:2px solid #009688;text-align:center;}.SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23,5,5,0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);color:lavender;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>Adjust Date, Day, Month and Year</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateAlarm'>ALARM</a></li></ul></div></div><div class='content'><form action='/setDate' method='post'><table class='InputTable'><tr><td><input class='TextBox' type='text' name='Date' id='Date' placeholder='Enter Date'></td></tr><tr><td><select name='month_num' id='selectionBox'><option value='0'>Select Month</option><option value='1'>January</option><option value='2'>February</option><option value='3'>March</option><option value='4'>April</option><option value='5'>May</option><option value='6'>June</option><option value='7'>July</option><option value='8'>August</option><option value='9'>September</option><option value='10'>October</option><option value='11'>November</option><option value='12'>December</option></select></td></tr><tr><td><input class='TextBox' type='text' name='Year' id='Year' placeholder='Enter Year'></td></tr><tr><td><select name='Day' id='selectionBox'><option value='0'>Select Day</option><option value='1'>Monday</option><option value='2'>Tuesday</option><option value='3'>Wednesday</option><option value='4'>Thursday</option><option value='5'>Friday</option><option value='6'>Saturday</option><option value='7'>Sunday</option></select></td></tr><tr><td><input class='SubmitButton' type='submit' value='Update'></td></tr></table></form></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
  server.send(200 , "text/html" , date_site);
}

void handleAlarm(){
  String alarm_site = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue,Arial,Helvetica,sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg,rgba(96,63,131,1) 0%,rgba(199,211,212,1) 1%,rgba(199,211,212,1) 99%,rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.InputTable{margin:auto;}.TextBox{margin-top:50px;height:50px;width:100%;border-radius:25px;border:2px solid #009688;text-align:center;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;}.navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);}#alarm{margin-top:50px;height:50px;width:100%;border-radius:25px;border:2px solid #009688;text-align-last:center;align-content:center;}.SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23,5,5,0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);color:lavender;}.#divide{color:rgba(199,211,255,1);background-color:rgba(199,211,255,1);height:2px;margin-left:auto;margin-top:50px;margin-bottom:50px;width:40%;}.SubmitBtn{margin-top:20px;width:50%;margin-left:25%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;background:transparent;color:rgba(23,5,5,0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitBtn:hover{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);color:lavender;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>Set alarm</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateDate'>DATE</a></li></ul></div></div><div class='content'><form action='/setAlarm' method='post'><table class='InputTable'><tr><td><input class='TextBox' type='text' id='Hour' name='Hour' placeholder='Enter Hour'></td></tr><tr><td><input class='TextBox' type='text' id='Min' name='Min' placeholder='Enter Minutes'></td></tr><tr><td><select id='alarm' name='alarm'><option id='list' value='AM'>AM</option><option id='list' value='PM'>PM</option></select></td></tr><tr><td><input class='SubmitButton' type='submit' value='Set Alarm'></td></tr></table></form><hr id='divide'><div class='modify'><a href='/alarm_off'><input class='SubmitBtn' type='submit' value='Turn off '></a></div></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
  server.send(200, "text/html", alarm_site);
}

void handleSetTime() {
  String Hour_ = server.arg("Hour");
  String Min_ = server.arg("Min");
  String Sec_ = server.arg("Sec");

  int newHour = Hour_.toInt();
  int newMin = Min_.toInt();
  int newSec = Sec_.toInt();

  if (newHour >= 0 && newHour < 24 && newMin >= 0 && newMin < 60 && newSec >= 0 && newSec < 60) {
    Hour = newHour;
    Min = newMin;
    Sec = newSec;

    String data_recieved = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg, rgba(96,63,131,1) 0%, rgba(199,211,212,1) 1%, rgba(199,211,212,1) 99%, rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.SubmitBtn{margin-top:50px;margin-left:25%;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;} .navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);} #Txt{margin-top:0;text-align:center;color:rgba(23, 5, 5, 0.771);}.SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23, 5, 5, 0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);color:lavender;}.InputTable{margin:auto;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>Adjust Time</h1></div><div class='title'><div class='navbar'><ul><li><a href='/updateAlarm'>ALARM</a></li><li><a href='/updateDate'>DATE</a></li></ul></div></div><div class='content'><table class='InputTable'><tr><td><h1 id='Txt'>Time Has<br>been updated</h1></td></tr><tr><td><a href='/'><input class='SubmitButton'  type='submit' value='Return'></a></td></tr></table></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
    server.send(200, "text/html", data_recieved);
  } else {
    String invalid = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg, rgba(96,63,131,1) 0%, rgba(199,211,212,1) 1%, rgba(199,211,212,1) 99%, rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.SubmitBtn{margin-top:50px;margin-left:25%;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;} .navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);} #Txt{margin-top:50%;text-align:center;color:rgba(23, 5, 5, 0.771);} .SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23, 5, 5, 0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);color:lavender;}.InputTable{margin:auto;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>INVALID INPUT</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateDate'>DATE</a></li><li><a href='/updateAlarm'>ALARM</a></li></ul></div></div><div class='content'><table class='InputTable'><tr><td><h1 id='Txt'>INVALID INPUT</h1></td></tr></table></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
    server.send(200, "text/html", invalid);
  }
}

void handleSetDate(){
  int old_month_num;
  int old_year;
  String Date_ = server.arg("Date");
  String Month_num_ = server.arg("month_num");
  String Year_ = server.arg("Year");
  String Day_ = server.arg("Day");

  int newDate = Date_.toInt();
  int newMonth_num = Month_num_.toInt();
  int newYear = Year_.toInt();
  int newDay_num = Day_.toInt();

  if(newMonth_num > 0 && newMonth_num <=12 && newDate > 0 && newDay_num >0 && newDay_num <=7){
    old_month_num = month_num;
    old_year = year;
    month_num = newMonth_num;
    year = newYear;
    fetchDaysInMonth();
    if(newDate <= daysInMonth){
      month_num = newMonth_num;
      date = newDate;
      year = newYear;
      day_num = newDay_num;
      fetchMonthName();
      fetchDayName();

      String data_recieved = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin: 0;}.header{height: 60px;width: 100%;background: linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top: 10px;}#Heading{margin: 0;text-align: center;color: lavender;font-family: Helvetica Neue, Arial, Helvetica, sans-serif;font-weight: bold;font-size: 100%;}.content{height: 750px;width: 100%;background: linear-gradient(0deg, rgba(96,63,131,1) 0%, rgba(199,211,212,1) 1%, rgba(199,211,212,1) 99%, rgba(96,63,131,1) 100%);} .footer{height: 60px;width: 100%;background: linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top: 15px;}#footer-text{margin: 0;text-align: center;color: lavender;}.SubmitBtn{margin-top: 50px;margin-left: 25%;}.navbar{width: 85%;padding: 35px 0;display: flex;align-items: center;justify-content: space-between;}.navbar ul li{list-style: none;display: inline-block;margin: 0 20px;position: relative;border: none;}.navbar ul li a{text-decoration: none;color: white;text-transform: uppercase;}.navbar ul li::after{content: '';height: 3px;background: #009688;position: absolute;left: 0;bottom: -10px;transition: 0.5s;border: none;}.navbar ul li:hover::after{width: 100%;}.title{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);}#Txt{margin-top: 0;text-align: center;color: rgba(23, 5, 5, 0.771);}.SubmitButton{margin-top: 20px;width: 100%;padding: 15px 0;text-align: center;border-radius: 25px;border: 2px solid #009688;margin-top: 50px;background: transparent;color: rgba(23, 5, 5, 0.771);cursor: pointer;position: relative;overflow: hidden;font-weight: bold;}.SubmitButton:hover{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);color: lavender;}.InputTable{margin: auto;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>Adjust Date</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateAlarm'>ALARM</a></li></ul></div></div><div class='content'><table class='InputTable'><tr><td><h1 id='Txt'>Date Has<br>been updated</h1></td></tr><tr><td><a href='/updateDate'><input class='SubmitButton'  type='submit' value='Return'></a></td></tr></table></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
      server.send(200, "text/html", data_recieved);
    }
      else{
      month_num = old_month_num;
      year = old_year;
      String invalid = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg,rgba(96,63,131,1) 0%,rgba(199,211,212,1) 1%,rgba(199,211,212,1) 99%,rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.SubmitBtn{margin-top:50px;margin-left:25%;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;}.navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);}.Txt{margin-top:0;text-align:center;color:rgba(23,5,5,0.771);}.SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23,5,5,0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg,#3E3458 0%,#5F4B8B 50%,#3E3458 100%);color:lavender;}.InputTable{margin:auto;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>INVALID INPUT</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateDate'>DATE</a></li><li><a href='/updateAlarm'>ALARM</a></li></ul></div></div><div class='content'><table class='InputTable'><tr><td><h1 class='Txt'>INVALID INPUT</h1></td></tr></table></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
      server.send(200, "text/html", invalid);
    }
  }
  else{
    month_num = old_month_num;
    year = old_year;
    String invalid = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg, rgba(96,63,131,1) 0%, rgba(199,211,212,1) 1%, rgba(199,211,212,1) 99%, rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.SubmitBtn{margin-top:50px;margin-left:25%;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;} .navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);} #Txt{margin-top:50%;text-align:center;color:rgba(23, 5, 5, 0.771);} .SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23, 5, 5, 0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);color:lavender;}.InputTable{margin:auto;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>INVALID INPUT</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateDate'>DATE</a></li><li><a href='/updateAlarm'>ALARM</a></li></ul></div></div><div class='content'><table class='InputTable'><tr><td><h1 id='Txt'>INVALID INPUT</h1></td></tr></table></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
    server.send(200, "text/html", invalid);
  }
}

void handleSetAlarm(){
  String al_H = server.arg("Hour");
  String al_M = server.arg("Min");
  String alarm_ampm_ = server.arg("alarm");

  int al_H_ = al_H.toInt();
  int al_M_ = al_M.toInt();

  if(al_H_ >= 1 && al_H_ <= 12 && al_M_ >= 0 && al_M_ < 60){
    alarm_H = al_H_;
    alarm_M = al_M_;
    alarm_ampm = alarm_ampm_;
    alarm_ = true;

    String g = "  ";
    g += alarm_H;
    g += ":";
    g += alarm_M;

    String alarmset = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg, rgba(96,63,131,1) 0%, rgba(199,211,212,1) 1%, rgba(199,211,212,1) 99%, rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.SubmitBtn{margin-top:50px;margin-left:25%;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;} .navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);} #Txt{margin-top:0;text-align:center;color:rgba(23, 5, 5, 0.771);}.SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23, 5, 5, 0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);color:lavender;}.InputTable{margin:auto;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>Set Alarm</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateDate'>DATE</a></li></ul></div></div><div class='content'><table class='InputTable'><tr><td><h1 id='Txt'>Alarm Has<br>been Set.</h1></td></tr><tr><td><a href='/updateAlarm'><input class='SubmitButton'  type='submit' value='Return'></a></td></tr></table></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
    server.send(200, "text/html", alarmset);
    Serial.println(g);
  }
  else{
    String invalid = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Clock</title><style>body{margin:0;}.header{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:10px;}#Heading{margin:0;text-align:center;color:lavender;font-family:Helvetica Neue, Arial, Helvetica, sans-serif;font-weight:bold;font-size:100%;}.content{height:750px;width:100%;background:linear-gradient(0deg, rgba(96,63,131,1) 0%, rgba(199,211,212,1) 1%, rgba(199,211,212,1) 99%, rgba(96,63,131,1) 100%);} .footer{height:60px;width:100%;background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);padding-top:15px;}#footer-text{margin:0;text-align:center;color:lavender;}.SubmitBtn{margin-top:50px;margin-left:25%;}.navbar{width:85%;padding:35px 0;display:flex;align-items:center;justify-content:space-between;}.navbar ul li{list-style:none;display:inline-block;margin:0 20px;position:relative;border:none;}.navbar ul li a{text-decoration:none;color:white;text-transform:uppercase;} .navbar ul li::after{content:'';height:3px;background:#009688;position:absolute;left:0;bottom:-10px;transition:0.5s;border:none;}.navbar ul li:hover::after{width:100%;}.title{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);} #Txt{margin-top:50%;text-align:center;color:rgba(23, 5, 5, 0.771);} .SubmitButton{margin-top:20px;width:100%;padding:15px 0;text-align:center;border-radius:25px;border:2px solid #009688;margin-top:50px;background:transparent;color:rgba(23, 5, 5, 0.771);cursor:pointer;position:relative;overflow:hidden;font-weight:bold;}.SubmitButton:hover{background:linear-gradient(90deg, #3E3458 0%, #5F4B8B 50%, #3E3458 100%);color:lavender;}.InputTable{margin:auto;}</style></head><body><div class='container'><div class='header'><h1 id='Heading'>NODEMCU ESP8266<br>MULTIFUNCTIONAL CLOCK<br><br>INVALID INPUT</h1></div><div class='title'><div class='navbar'><ul><li><a href='/'>TIME</a></li><li><a href='/updateDate'>DATE</a></li><li><a href='/updateAlarm'>ALARM</a></li></ul></div></div><div class='content'><table class='InputTable'><tr><td><h1 id='Txt'>INVALID INPUT</h1></td></tr></table></div><div class='footer'><p id='footer-text'> Developed by : Nikhil Biby</p></div></div></body></html>";
    server.send(200, "text/html", invalid);
  }
}

void fetchMonthName(){
  switch(month_num){
      case 1:
        monthName = "Jan";
        break;
      case 2:
        monthName = "Feb";
        break;
      case 3:
        monthName = "Mar";
        break;
      case 4:
        monthName = "Apr";
        break;
      case 5:
        monthName = "May";
        break;
      case 6:
        monthName = "Jun";
        break;
      case 7:
        monthName = "Jul";
        break;
      case 8:
        monthName = "Aug";
        break;
      case 9:
        monthName = "Sep";
        break;
      case 10:
        monthName = "Oct";
        break;
      case 11:
        monthName = "Nov";
        break;
      case 12:
        monthName = "Dec";
        break; 
    }
}
void fetchDayName(){
  switch(day_num){
    case 1:
      day = "Mon";
      break;
    case 2:
      day = "Tue";
      break;
    case 3:
      day = "Wed";
      break;
    case 4:
      day = "Thu";
      break;
    case 5:
      day = "Fri";
      break;
    case 6:
      day = "Sat";
      break;
    case 7:
      day = "Sun";
      break;
  }
}
void fetchDaysInMonth(){
  if(month_num == 4 || month_num == 6 || month_num == 9 || month_num == 9){
    daysInMonth = 30;
  }
  if(month_num == 1 || month_num == 3 || month_num == 5 || month_num == 7 || month_num == 8 || month_num == 10 || month_num == 12){
    daysInMonth = 31;
  }
  if(month_num == 2){
    if(year%4 == 0){
      daysInMonth = 29;
    }
    else{
      daysInMonth = 28;
    }
  }
}

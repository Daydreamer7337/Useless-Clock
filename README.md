<img width="1280" alt="readme-banner" src="https://github.com/user-attachments/assets/35332e92-44cb-425b-9dff-27bcf1023c6c">

# Useless Clock 🎯


## Basic Details
### Team Name: Nikhil Biby's Team


### Team Members
- Team Lead: Nikhil Biby - Viswajyothi College Of Engineering And Technology, Vazhakulam

### Project Description
Basic clock functions like time, date, day, month, year and alarm features are available on this. Made in Arduino IDE with esp 8266, driving a 16 x 1 LCD display. Alarm function is also available. All of these features can be configured through a locally hosted website.

### The Problem (that doesn't exist)
Who cares to go throgh the hassle of checking their watch to know the time, when you can have a better version of those ;)

### The Solution (that nobody asked for)
So we made a Clock that makes you update its time through your phone.

## Technical Details
### Technologies/Components Used
For Software:
- We used HTML to cretae the websites and C++ to implement it in Node MCU.
- Libraries used are LiquidCrystal, ESP8266WiFi, ESP8266WebServer.
- This project is developed in arduino IDE.

For Hardware:
- Main components are ESP8266, 16x1 LCD display, IR sensor, Buzzer, 10kohm potentiometer.
- Can accuretely show time for long periods, at low power consumption
- Breadboard, A computer?

### Implementation
Used Arduino IDE
# Installation
No installations required, power it up and go!

# Run
On turning on the clock, connect to the WiFi hotspot named "Clock". On connecting, open your browser and type in the ip "192.168.1.1" in the address bar. Adjust date and time in the displayed website.

# Screenshots (Add at least 3)
<img width="1200" alt="arduino_ide_screenshot" src="https://github.com/Daydreamer7337/Useless-Clock/blob/9f7585364026a302bd6e81cba5905be875096424/Images/Arduino_ss1.jpg">
Code in Arduino IDE.

<img width="1200" alt="Website_code" src="https://github.com/Daydreamer7337/Useless-Clock/blob/9f7585364026a302bd6e81cba5905be875096424/Images/Website_ss1.jpg">
Website under development.

<img width="1920" alt="Website_appearance" src="https://github.com/Daydreamer7337/Useless-Clock/blob/9f7585364026a302bd6e81cba5905be875096424/Images/Website_ss2.jpg">
Completed website.

# Diagrams
<img width="1200" alt="CircuitDiagram" src="https://github.com/Daydreamer7337/Useless-Clock/blob/5351353fa0f2df5a5b0ad9fa465da6d12199f0c7/Images/Diagram.jpg">
Circuit Diagarm. Connections are as given below:
 - LCD RS pin to digital pin D0
 - LCD Enable pin to digital pin D1
 - LCD D4 pin to digital pin D2
 - LCD D5 pin to digital pin D3
 - LCD D6 pin to digital pin D4
 - LCD D7 pin to digital pin D5
 - LCD R/W pin to ground
 - LCD VSS pin to ground
 - LCD VCC pin to 5V
 - 10K resistor:
 - ends to +5V and ground
 - wiper to LCD VO pin (pin 3)
 - A to +5e
 - K to ground
 - Buzzer +ve pin to digital pin D6
 - Buzzer -ve pin to ground
 - IR sensor OUT pin to digital pin D7
 - IR sensor VCC pin to 5V
 - IR sensor GND pin to ground
 
# Build Photos
<img width="1079" alt="Circuit Being Made" src="https://github.com/Daydreamer7337/Useless-Clock/blob/5351353fa0f2df5a5b0ad9fa465da6d12199f0c7/Images/Making_1.jpg">
Circuit is being wired.

<img width="1080" alt="Completed Circuit" src="https://github.com/Daydreamer7337/Useless-Clock/blob/5351353fa0f2df5a5b0ad9fa465da6d12199f0c7/Images/Making_2.jpg">
  Circuit is wired as per given above on bread board. Its is powered. A device is connected to its wifi newtwork and the time can be adjusted through the ip 192.168.1.1

### Project Demo
# Video
https://drive.google.com/file/d/1cSRRx6zWlV5za5vh6XPp75ZeI7u50nt1/view?usp=drivesdk
This video shows time being updated through website. Similarly, the date, say, month and year can be adjusted through this website. Alarm can also be set in a similar way. When ringing, the alarm can be turned off by either hovering your hand over the IR sensor or by clicking turn off alarm button in website.

## Team Contributions
- Nikhil Biby: HTML, C++ and wiring(everything)

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProject--24-24?link=https%3A%2F%2Fwww.tinkerhub.org%2Fevents%2FQ2Q1TQKX6Q%2FUseless%2520Projects)

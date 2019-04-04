# The ESP Wardriving Project
Bringing wardriving to the ESP platform for ESP8266 and ESP32. 

## Overview
This project uses a Ublox GPS to grab GPS coordinates and the ESP's Wi-Fi integration to log Wi-Fi AP information in a CSV file onto a microSD card.

## Dependencies (Arduino)
Adafruit GFX 
Adafruit SSD1306
TinyGPS++

## Pinout
Pinout for TFT.
Display | NodeMCU 
--------|--------- 
LED     | +3V3 
SCK     | D5 
SDA     | D7 
A0      | D4 
RESET   | +3V3 
CS      | D8 
GND     | GND 
VCC     | +3V3 

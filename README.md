# ESP-DriveBy 
ESP-DriveBy brings wardriving to the ESP8266 platform at a cheap cost.  Wardriving allows a person to log Wi-Fi SSID's and other attributes which can show Wi-Fi locations on a map and other information.  This often requires setting up complicated and excessive, bulky gear.  This project utilizes the ESP8266, a GPS, and an SD logger all in a small platform.

## Overview
This project uses a Ublox GPS to grab GPS coordinates and the ESP's Wi-Fi integration to log Wi-Fi AP information in a CSV file onto a microSD card.  This file can be used with Google MyMaps for tying coordinates with SSID's.

## Dependencies (Arduino)
Adafruit GFX   
Adafruit SSD1306  
TinyGPS++   

## Pinout
Pinout for TFT. 

|Display | NodeMCU |
|--------|---------|  
|LED     | +3V3    |
|SCK     | D5      |
|SDA     | D7      |
|A0      | D4      |
|RESET   | +3V3    |
|CS      | D8      |
|GND     | GND     |
|VCC     | +3V3    |

## Stuff to add
- Shift from UTC timezone.  
- NeoGPS lib?
- Parse new values on input.
- Cross for Feather/NodeMCU

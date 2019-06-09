// ESP-DriveBy (TFT)

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h> // TFT
#include <ESP8266WiFi.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <TinyGPS++.h>

#define SerialMonitor Serial
int loops=0;
double tmp_lat= 0;
double tmp_lng= 0;
int tmp_min=0;
String ssid= "";
const unsigned char bmp [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x3F, 0xFF, 0xC0, 0x03, 0xF8, 0x01, 0xF8, 0x00, 0x00, 0x4F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x3F, 0xFF, 0xC0, 0x0F, 0xF8, 0x07, 0xBE, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00,
0x00, 0x31, 0x00, 0x00, 0x1F, 0x00, 0x07, 0x03, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00,
0x00, 0x30, 0x00, 0x00, 0x3E, 0x00, 0x07, 0x01, 0xC0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00,
0x00, 0x30, 0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00,
0x00, 0x10, 0x00, 0x00, 0xD0, 0x00, 0x07, 0x00, 0x40, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
0x00, 0x10, 0x00, 0x00, 0x90, 0x00, 0x07, 0x00, 0x40, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x00, 0x90, 0x00, 0x07, 0x00, 0x40, 0x00, 0x30, 0x00, 0x0C, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x00, 0xD8, 0x00, 0x07, 0x00, 0xC0, 0x00, 0x7C, 0x00, 0x06, 0x00, 0x00, 0x00,
0x00, 0x18, 0x03, 0x80, 0x3C, 0x00, 0x07, 0x00, 0xC0, 0x00, 0x7E, 0x00, 0x07, 0x00, 0x00, 0x00,
0x00, 0x18, 0x3C, 0xF0, 0x1E, 0x00, 0x07, 0x01, 0x80, 0x00, 0x17, 0xC0, 0x03, 0x00, 0x00, 0x00,
0x00, 0x1F, 0xFF, 0xE0, 0x07, 0x80, 0x07, 0x0F, 0x80, 0x00, 0x01, 0xF0, 0x01, 0x80, 0x00, 0x00,
0x00, 0x1B, 0xFF, 0xC0, 0x01, 0xE0, 0x07, 0xFD, 0xC0, 0x00, 0x00, 0x1E, 0x00, 0xC0, 0x00, 0x00,
0x00, 0x18, 0x00, 0x00, 0x00, 0x70, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x07, 0x00, 0x60, 0x00, 0x00,
0x00, 0x18, 0x00, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x30, 0x00, 0x00,
0x00, 0x1C, 0x00, 0x00, 0x00, 0x3C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x00, 0x00,
0x00, 0x18, 0x00, 0x00, 0x00, 0x1C, 0x07, 0x00, 0x00, 0x00, 0x70, 0x00, 0xC0, 0x18, 0x00, 0x00,
0x00, 0x18, 0x00, 0x00, 0x00, 0x1C, 0x07, 0x80, 0x00, 0x00, 0x5F, 0x00, 0x60, 0x18, 0x00, 0x00,
0x00, 0x18, 0x00, 0x00, 0x00, 0x3C, 0x07, 0x80, 0x00, 0x00, 0x07, 0xC0, 0x20, 0x18, 0x00, 0x00,
0x00, 0x08, 0x00, 0x00, 0x10, 0x3C, 0x07, 0x80, 0x00, 0x00, 0x03, 0xE0, 0x20, 0x08, 0x00, 0x00,
0x00, 0x08, 0x00, 0x00, 0x30, 0x58, 0x07, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x20, 0x08, 0x00, 0x00,
0x00, 0x0C, 0x00, 0x00, 0x38, 0xF8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x78, 0x20, 0x08, 0x00, 0x00,
0x00, 0x0C, 0x00, 0x00, 0x0F, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x38, 0x30, 0x08, 0x00, 0x00,
0x00, 0x0F, 0xFF, 0xF0, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x18, 0x1C, 0x30, 0x08, 0x00, 0x00,
0x00, 0x07, 0xC7, 0xE0, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x14, 0x1C, 0x10, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x34, 0x0C, 0x10, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x0C, 0x10, 0x0C, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x04, 0x10, 0x0C, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x04, 0x10, 0x04, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x0B, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1D, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1B, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1C, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x00, 0x01, 0x81, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x40, 0x00, 0xE0, 0x00, 0x00, 0x01, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x40, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x83, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x60, 0x00, 0x00, 0x10, 0x3F, 0x01, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x00, 0x60, 0xF8, 0x60, 0x10, 0x79, 0x80, 0x84, 0x31, 0x00, 0x10, 0x00, 0x00, 0x00,
0x00, 0x08, 0x00, 0x61, 0xFC, 0x61, 0x18, 0x5B, 0x00, 0x80, 0x19, 0x80, 0x30, 0x00, 0x00, 0x00,
0x00, 0x08, 0x00, 0x61, 0xC0, 0xC1, 0x18, 0xFE, 0x00, 0x80, 0x18, 0xF0, 0x30, 0x00, 0x00, 0x00,
0x00, 0x08, 0x00, 0x63, 0xC0, 0x61, 0x18, 0xC0, 0x00, 0x80, 0x18, 0x3C, 0x70, 0x00, 0x00, 0x00,
0x00, 0x08, 0x00, 0xE3, 0x80, 0x41, 0x98, 0xE0, 0x00, 0x80, 0x30, 0x0E, 0x60, 0x00, 0x00, 0x00,
0x00, 0x08, 0x00, 0xC3, 0x80, 0x40, 0x90, 0x70, 0x80, 0x80, 0x30, 0x07, 0x60, 0x00, 0x00, 0x00,
0x00, 0x08, 0x01, 0xC3, 0x80, 0x40, 0xF0, 0x3F, 0xE1, 0x80, 0x60, 0x03, 0xE0, 0x00, 0x00, 0x00,
0x00, 0x0C, 0x03, 0x81, 0x80, 0x40, 0xF0, 0x00, 0x01, 0xFF, 0xC0, 0x03, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x0C, 0x07, 0x80, 0x80, 0x40, 0x50, 0x00, 0x01, 0xE0, 0x80, 0x01, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x0E, 0x19, 0x00, 0x80, 0x40, 0x50, 0x00, 0x01, 0xBF, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x0F, 0xF3, 0x00, 0x00, 0x40, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
0x00, 0x0C, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

Adafruit_ST7735 tft =Adafruit_ST7735(4, 5, -1); // CS, DC, RST (sentinel)

#define SD_CS 2
#define LOG_FILE_PREFIX "log"
#define LOG_FILE_SUFFIX "csv"
#define MAX_LOG_FILES 100

char logFileName[13];
#define LOG_COLUMN_COUNT 11
const String wigleHeaderFileFormat = "WigleWifi-1.4,appRelease=2.26,model=Feather,release=0.0.0,device=arduinoWardriving,display=3fea5e7,board=esp8266,brand=Adafruit";
char * log_col_names[LOG_COLUMN_COUNT] = {
  "MAC", "SSID", "AuthMode", "FirstSeen", "Channel", "RSSI", "CurrentLatitude", "CurrentLongitude", "AltitudeMeters", "AccuracyMeters", "Type"
};

#define LOG_RATE 500
unsigned long lastLog = 0;

static const int RX = 0, TX = 15;
static const uint32_t GPSBaud = 9600;
SoftwareSerial ss(RX, TX); // RT
TinyGPSPlus tinyGPS;

int display = 1;

void setup() {
  SerialMonitor.begin(115200);
  tft.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
  
  tft.fillScreen(ST77XX_BLACK);
  tft.drawBitmap(0,0,bmp,128,160, 0xFFFF);
  tft.setCursor(30,140);
  tft.println("By Alex Lynd");
  tft.setCursor(0,0);
  delay(2000);
  
  tft.fillScreen(ST77XX_BLACK);
  
  tft.setTextSize(1);

  ss.begin(GPSBaud);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  tft.println("***  ESP-DriveBy  ***\n");
  tft.println("Serial monitor ready");
  tft.println("Baud rate: 115200\n");
  Serial.println("\nESP-DriveBy | alexlynd.com/projects/ESP-DriveBy");
  Serial.println("***");
  initializeSD();
  Serial.println("***");
  tft.println();
  initializeGPS();
  
}
void initializeGPS(){
  tft.print("GPS: ");
  Serial.print("GPS ");
  if (millis() > 5000 && tinyGPS.charsProcessed() < 10) {
    tft.setTextColor(ST77XX_RED);
    tft.println("not found");
    Serial.print("not detected, check wiring, baud rate or reset board.");
    while (true)
      if (!(millis() > 5000 && tinyGPS.charsProcessed() < 10))
        break;
  }
  tft.setTextColor(ST77XX_GREEN);
  tft.println("found");
  Serial.print("detected, waiting for a fix.");
  tft.setTextColor(ST77XX_WHITE); 
  tft.println("Baud rate: 9600");
  tft.println("Waiting on GPS fix...");
}
void lookForNetworks() { // main stuff here
  int n = WiFi.scanNetworks();
  if (n == 0) { SerialMonitor.println("no networks found"); } 
  else {
    for (uint8_t i= 1; i <= n; ++i) {
      if ((isOnFile(WiFi.BSSIDstr(i)) == -1) && (WiFi.channel(i) > 0) && (WiFi.channel(i) < 15)) { // Avoid erroneous channels
        File logFile = SD.open(logFileName, FILE_WRITE);
        tft.setCursor(0,20);
        tft.fillRect(23,20,128,70,ST77XX_BLACK);
        //SerialMonitor.println("New network found");

        Serial.println("***********");
        Serial.print(tinyGPS.date.month()); Serial.print("/");
        Serial.print(tinyGPS.date.day()); Serial.print("/");
        Serial.print(tinyGPS.date.year()); Serial.print(" ");   
        Serial.print(tinyGPS.time.hour()); Serial.print(":");
        Serial.print(tinyGPS.time.minute()); Serial.print(":");
        Serial.println(tinyGPS.time.second()); 
          
        logFile.print(WiFi.BSSIDstr(i)); logFile.print(',');
        Serial.print("BSSID: "); Serial.println(WiFi.BSSIDstr(i));
        tft.setTextColor(ST77XX_RED);
        tft.print("BSS:");
         tft.setTextColor(ST77XX_WHITE);
        tft.println(WiFi.BSSIDstr(i)); //TFT
        
        logFile.print(WiFi.SSID(i));     logFile.print(',');
        tft.setTextColor(ST77XX_RED);
        tft.print("ESS:");
        Serial.print("ESSID: "); Serial.println(WiFi.SSID(i));
        tft.setTextColor(ST77XX_WHITE);
        if (WiFi.isHidden(i)){
          tft.println("*hidden*");
          SerialMonitor.print("Found a hidden: "); SerialMonitor.println(WiFi.BSSIDstr(i));
        }
        else{
          if (WiFi.SSID(i).length()>17) {
            ssid= WiFi.SSID(i).substring(0,14)+"...";
            tft.println(ssid);
          }
          else { tft.println(WiFi.SSID(i)); }
        }
        logFile.print(getEncryption_header(i)); logFile.print(',');
        tft.setTextColor(ST77XX_RED);
        Serial.print("Encryption: ");
        Serial.println(getEncryption(i));
        tft.print("ENC:");
        tft.setTextColor(ST77XX_WHITE);
        tft.println(getEncryption(i));
        logFile.print(tinyGPS.date.year());   logFile.print('-');
        logFile.print(tinyGPS.date.month());  logFile.print('-');
        logFile.print(tinyGPS.date.day());    logFile.print(' ');
        logFile.print(tinyGPS.time.hour());   logFile.print(':');
        logFile.print(tinyGPS.time.minute()); logFile.print(':');
        logFile.print(tinyGPS.time.second()); logFile.print(',');
        logFile.print(WiFi.channel(i)); logFile.print(',');
        tft.setTextColor(ST77XX_RED);
        tft.print("CH :"); 
        tft.setTextColor(ST77XX_WHITE);
        tft.println(WiFi.channel(i));
        Serial.print("Channel: "); Serial.println(WiFi.channel(i));
        logFile.print(WiFi.RSSI(i));    logFile.print(',');
        tft.setTextColor(ST77XX_RED);
        tft.print("RSSI:"); 
        tft.setTextColor(ST77XX_WHITE);
        tft.println(WiFi.RSSI(i));
        Serial.print("RSSI (strength): "); Serial.println(WiFi.RSSI(i)); 
        logFile.print(tinyGPS.location.lat(), 6); logFile.print(',');
        logFile.print(tinyGPS.location.lng(), 6); logFile.print(',');
        logFile.print(tinyGPS.altitude.meters(), 1); logFile.print(',');
        logFile.print((tinyGPS.hdop.value(), 1));    logFile.print(',');
        logFile.print("WIFI");
        logFile.println();
        logFile.close();
        tft.println();
        tft.print("Networks seen: "); tft.println(countNetworks());
        Serial.print("Networks logged so far: "); Serial.println(countNetworks());
      }
    }
  }
}
void loop() {
  
  tft.setTextColor(ST77XX_WHITE);
  if (tinyGPS.location.isValid()) {
    if (loops==0) {
      tft.print("Lat: "); tft.println(tinyGPS.location.lat(), 7);
      tft.print("Lon: "); tft.println(tinyGPS.location.lng(), 7);
      Serial.println("Initial fix:"); 
      Serial.print("Lat: "); Serial.println(tinyGPS.location.lat(), 7);
      Serial.print("Lon: "); Serial.println(tinyGPS.location.lng(), 7); 
      Serial.println("All processes good, starting ESP-DriveBy");
      Serial.println("***");
      tft.println("\nStarting ESP-DriveBy!");
      delay(2000);
      tft.fillScreen(ST77XX_BLACK);
      loops=1;
    }
    else { /* non startup run */
      
      tft.setCursor(32,0);
      if (tmp_min!= tinyGPS.time.minute()) { /* TIME */
        tft.fillRect(32,0,65,7,ST77XX_BLACK);
        tmp_min= tinyGPS.time.minute();      
      }
      tft.printf("%02d",tinyGPS.date.month());tft.print("/");
      tft.printf("%02d",tinyGPS.date.day()); tft.print(" ");
      tft.printf("%02d",tinyGPS.time.hour()); tft.print(":");
      tft.printf("%02d",tinyGPS.time.minute());
      tft.drawLine(30,0,30,8,ST77XX_WHITE);
      tft.drawLine(30,8,98,8,ST77XX_WHITE);
      tft.drawLine(98,8,98,0,ST77XX_WHITE);
      lookForNetworks();
      
      tft.setCursor(0,144);  /* COORD */
      tft.drawLine(0,142,127,142,ST77XX_WHITE);
      tft.fillRect(30,144,85,16,ST77XX_BLACK);
      tft.print("Lat: "); tft.println(tinyGPS.location.lat(), 7); 
      tft.print("Lon: "); tft.println(tinyGPS.location.lng(), 7);
      
    }
  }

  smartDelay(LOG_RATE);
  if (millis() > 5000 && tinyGPS.charsProcessed() < 10)
    SerialMonitor.println("GPS not found");
}

static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      tinyGPS.encode(ss.read());
  } while (millis() - start < ms);
}

int countNetworks() {
  File netFile = SD.open(logFileName);
  int networks = 0;
  if (netFile) {
    while (netFile.available()) {
      netFile.readStringUntil('\n');
      networks++;
    }
    netFile.close();
    if (networks == 0) {
      return networks;
    } else {
      return (networks - 1); //Avoid header count
    }
  }
}

int isOnFile(String mac) {
  File netFile = SD.open(logFileName);
  String currentNetwork;
  if (netFile) {
    while (netFile.available()) {
      currentNetwork = netFile.readStringUntil('\n');
      if (currentNetwork.indexOf(mac) != -1) { // already found
        netFile.close();
        return currentNetwork.indexOf(mac);
      }
    }
    netFile.close();
    return currentNetwork.indexOf(mac);
  }
}

void initializeSD() {
  tft.print("SD card: ");
  if (!SD.begin(SD_CS)) {
    tft.setTextColor(ST77XX_RED);
    tft.println("not found");
    Serial.print("SD card not detected, waiting...");
    tft.setTextColor(ST77XX_WHITE);
    tft.println("Waiting on SD card...");
    while (true)
      if (SD.begin(SD_CS))
        break;
  }
  tft.setTextColor(ST77XX_BLACK);  // cover by printing in black
  tft.setCursor(54,40);
  tft.println("not found");
  tft.println("Waiting on SD card...");
  tft.setCursor(55,40);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("found");
  Serial.println("SD card detected!");
  for (int i=0; i< MAX_LOG_FILES; i++) {
    memset(logFileName, 0, strlen(logFileName));
    sprintf(logFileName, "%s%d.%s", LOG_FILE_PREFIX, i, LOG_FILE_SUFFIX);
    if (!SD.exists(logFileName)) { break; } 
  }
  tft.setTextColor(ST77XX_WHITE);
  tft.print("Creating: ");
  tft.println(logFileName);
  Serial.println("Creating "); Serial.println(logFileName);
  File logFile = SD.open(logFileName, FILE_WRITE);
  if (logFile) {
    int i = 0;
    logFile.println(wigleHeaderFileFormat);
    for (; i < LOG_COLUMN_COUNT; i++) {
      logFile.print(log_col_names[i]);
      if (i < LOG_COLUMN_COUNT - 1)
        logFile.print(',');
      else
        logFile.println();
    }
    logFile.close();
  }
}

String getEncryption_header(uint8_t network) {
  byte encryption = WiFi.encryptionType(network);
  switch (encryption) {
    case 2:
      return "[WPA-PSK-CCMP+TKIP][ESS]";
    case 5:
      return "[WEP][ESS]";
    case 4:
      return "[WPA2-PSK-CCMP+TKIP][ESS]";
    case 7:
      return "[ESS]";
    case 8:
      return "[WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][ESS]";
  }
}
String getEncryption(uint8_t network) { // for return on tft
  byte encryption = WiFi.encryptionType(network);
  switch (encryption) {
    case 2:
      return "WPA/PSK";
    case 5:
      return "WEP";
    case 4:
      return "WPA2/PSK";
    case 7:
      return "OPEN";
    case 8:
      return "WPA/WPA2/PSK";
  }
}
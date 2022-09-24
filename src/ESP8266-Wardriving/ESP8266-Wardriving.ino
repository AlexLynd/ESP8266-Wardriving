#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <TimeLib.h>   

#define UTC_offset -7  // PDT
#define SD_CS      D8

Adafruit_SSD1306 display(128, 64, &Wire, -1);  // shared reset

#if (SSD1306_LCDHEIGHT != 64)
#error("Incorrect screen height, fix Adafruit_SSD1306.h");
#endif

String logFileName = "";
int networks = 0;

#define LOG_RATE 500
char currentTime[5];
        
SoftwareSerial ss(D4, D3); // RX, TX
TinyGPSPlus tinyGPS;

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // OLED address
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  WiFi.mode(WIFI_STA); WiFi.disconnect();
  display.println("* ESP8266 WarDriver *\n");

  /* initialize SD card */
  display.print("SD Card: ");
  if (!SD.begin(SD_CS)) {
    display.println("not found"); display.display(); Serial.println("not found");
    while (!SD.begin(SD_CS));
  }
  display.setCursor(54, 16); display.setTextColor(BLACK);
  display.println("not found");
  display.setCursor(54, 16); display.setTextColor(WHITE);
  display.println("found"); display.display(); Serial.println("found");
  initializeSD();

  /* initialize GPS */
  delay(500);
  display.println();
  if (ss.available() > 0) {
    display.println("GPS: found");
    display.println("Waiting on fix...");
  }
  else {
    display.println("GPS: not found");
    display.println("Check wiring & reset.");
  }
  display.display();
  while (!tinyGPS.location.isValid()) {
    Serial.println(tinyGPS.location.isValid());
    delay(0);
    smartDelay(500);
  }
  display.println("(" + String(tinyGPS.location.lat(), 5) + "," + String(tinyGPS.location.lng(), 5) + ")");
  display.display();

  display.clearDisplay();
}
void lookForNetworks() {
  display.fillRect(48,0,30,7,BLACK);
  display.setCursor(48, 0);
  sprintf_P(currentTime, PSTR("%02d:%02d"),hour(),minute());
  display.println(currentTime); 
  display.drawLine(0,3,46,3,WHITE);
  display.drawLine(79,3,128,3,WHITE);
  display.display();
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("no networks found");
  }
  else {
    for (int i = 0; i < n; ++i) {
      if ((WiFi.channel(i) > 0) && (WiFi.channel(i) < 15)) {
        display.clearDisplay();
        display.setCursor(48, 0);
        sprintf_P(currentTime, PSTR("%02d:%02d"),hour(),minute());
        display.println(currentTime);    
        display.drawLine(0,3,46,3,WHITE);
        display.drawLine(79,3,128,3,WHITE);
        display.display();    
        networks++;
        File logFile = SD.open(logFileName, FILE_WRITE);
        logFile.print(WiFi.BSSIDstr(i));  logFile.print(',');
        logFile.print(WiFi.SSID(i)); logFile.print(',');
        display.setCursor(0,10);
        if (WiFi.SSID(i).length() > 20) { display.println(WiFi.SSID(i).substring(0, 18 ) + "..."); }
        else { display.println(WiFi.SSID(i)); }
        String bssid = WiFi.BSSIDstr(i);
        bssid.replace(":", "");
        display.println(bssid + "    (" + WiFi.RSSI(i) + ")");
        logFile.print(getEncryption(i,"")); logFile.print(',');
        display.print("Enc: "+getEncryption(i,"screen"));
        display.println("   Ch: "+ String(WiFi.channel(i)));    
        display.println();    
        display.setCursor(0,40);
        logFile.print(year());   logFile.print('-');
        logFile.print(month());  logFile.print('-');
        logFile.print(day());    logFile.print(' ');
        logFile.print(hour());   logFile.print(':');
        logFile.print(minute()); logFile.print(':');
        logFile.print(second()); logFile.print(',');
        logFile.print(WiFi.channel(i)); logFile.print(',');
        logFile.print(WiFi.RSSI(i)); logFile.print(',');
        logFile.print(tinyGPS.location.lat(), 6); logFile.print(',');
        logFile.print(tinyGPS.location.lng(), 6); logFile.print(',');
        display.println("Networks: " + String(networks));
        display.print(String(int(tinyGPS.speed.mph())) + " MPH");
        display.println(" Sats: " + String(tinyGPS.satellites.value()));
        display.println("(" + String(tinyGPS.location.lat(), 5) + "," + String(tinyGPS.location.lng(), 5) + ")");
        logFile.print(tinyGPS.altitude.meters(), 1); logFile.print(',');
        logFile.print(tinyGPS.hdop.value(), 1); logFile.print(',');
        logFile.println("WIFI");
        logFile.close();
        display.display();
        if (getEncryption(i,"")=="[WEP][ESS]"){  // flash if WEP detected
          display.invertDisplay(true);  delay(200);
          display.invertDisplay(false); delay(200);
          display.invertDisplay(true);  delay(200);
          display.invertDisplay(false); delay(200);
        }
      }
    }
  }
}
void loop() {
  if (tinyGPS.location.isValid()) {
    setTime(tinyGPS.time.hour(), tinyGPS.time.minute(), tinyGPS.time.second(), tinyGPS.date.day(), tinyGPS.date.month(), tinyGPS.date.year());
    adjustTime(UTC_offset * SECS_PER_HOUR);  
    lookForNetworks();
  }
  smartDelay(LOG_RATE);
  if (millis() > 5000 && tinyGPS.charsProcessed() < 10)
    Serial.println("No GPS data received: check wiring");
}

static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      tinyGPS.encode(ss.read());
  } while (millis() - start < ms);
}

// int isOnFile(String mac) {
//   File netFile = SD.open(logFileName);
//   String currentNetwork;
//   if (netFile) {
//     while (netFile.available()) {
//       currentNetwork = netFile.readStringUntil('\n');
//       if (currentNetwork.indexOf(mac) != -1) {
//         netFile.close();
//         return currentNetwork.indexOf(mac);
//       }
//     }
//     netFile.close();
//     return currentNetwork.indexOf(mac);
//   }
// }

void initializeSD() { // create new CSV file and add WiGLE headers
  int i = 0; logFileName = "log0.csv";
  while (SD.exists(logFileName)) {
    i++; logFileName = "log" + String(i) + ".csv";
  }
  File logFile = SD.open(logFileName, FILE_WRITE);
  display.println("Created: " + logFileName); display.display();
  if (logFile) {
    logFile.println("WigleWifi-1.4,appRelease=2.53,model=D1-Mini-Pro,release=0.0.0,device=NetDash,display=SSD1306,board=ESP8266,brand=Wemos");
    logFile.println("MAC,SSID,AuthMode,FirstSeen,Channel,RSSI,CurrentLatitude,CurrentLongitude,AltitudeMeters,AccuracyMeters,Type");
  }
  logFile.close();
}

String getEncryption(uint8_t network, String src) { // return encryption for WiGLE or print
  byte encryption = WiFi.encryptionType(network);
  switch (encryption) {
    case 2:
      if (src=="screen") { return "WPA"; }
      return "[WPA-PSK-CCMP+TKIP][ESS]";
    case 5:
      if (src=="screen") { return "WEP"; }
      return "[WEP][ESS]";
    case 4:
      if (src=="screen") { return "WPA2"; }
      return "[WPA2-PSK-CCMP+TKIP][ESS]";
    case 7:
      if (src=="screen") { return "NONE" ; }
      return "[ESS]";
    case 8:
      if (src=="screen") { return "AUTO"; }
      return "[WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][ESS]";
  }
}

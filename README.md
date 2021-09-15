# ESP8266 Wardriving
A compilation of scripts and resources for wardriving on the [ESP8266 WiFi microcontroller](https://www.espressif.com/en/products/socs/esp8266), including data visualization tools in Jupyter Notebook.

Documentation on this page is still in development.

## Components
Any ESP8266-based board should work with the basic required components, but the D1 mini form factor is highly recommended since using modules (such as for SD logging + battery management) can be done using plug-and-play hardware in a small footprint. All linked components are D1 mini compatible. 

**Required Components:**
| Component | Purpose |
| --- | --- |
| ESP8266 | Gather WiFi data & control hardware modules
| SD Reader | Store data that we can analyze with WiGLE / Python |
| GPS Module | Grab geolocation data + timestamp |

**Optional Components:**
| Component | Purpose | 
| --- | --- |
| 128x64 OLED | Get a visual display of WiFi data being captured |
| LiPo Battery | Power your ESP8266 for portable applications |
| Battery Module | Manage power for your ESP8266 w/ a LiPo battery |
| 100K Ω Resistor | Optional to read in battery level w/ the D1 Mini |
   
## Hardware Setup

**SD Reader Module** 
| SD Reader Pin | ESP8266 GPIO | D1 Mini Pin |
| --- | --- | --- |
| MISO | GPIO12 | D6 |
| MOSI | GPIO13 | D7 |
| SCK | GPIO14 | D5 |
| CS | GPIO15 | D8 |

**GPS Module** 
| GPS Pin | ESP8266 GPIO | D1 Mini Pin |
| --- | --- | --- |
| TX | GPIO2 | D4 |
| RX | GPIO0 | D3 |

## Data Visualization Scripts

Data Visualization Tutorial: https://www.youtube.com/watch?v=pFHUPs51CRQ

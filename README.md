# Arduino-Wetterstation
eine Keine Wetterstation für Ardoino

Diese Programm steuer mehere Sensoren an und gebt dies über die Ethernet eine XML Datei aus und Speicher alle Daten auch auf eine SD Katre als CSV Datei.

### Bauteile
- Mega 2560 von Elegoo (Endsprich den Aruino Mega)
- W5100 Ethernet Shield von Keyestudio
- DS18B20 (Temperatur Sensor)
- 4,7 kOhm Widerstand
- DHT11 oder DHT22 (Lufteuchte und Temperatur Sensor)
- BMP085 (Luftdruck Sensor)

### Belegung
- DS18B20 auf pin 7 + v5 + GND
- DHT11 / DHT22 auf 8 + v5 + GND
- BMP085 auf 20 (SDA) + 21 (SCL) + v3,3 + GND

### Install
Herunterladen Ardoino Ordner inhalt mit Aruino Programm offen volgende Bibliotheken Instaliren
- Ethernet
- OneWire
- DallasTemperature
- SPI
- SD
- dht11
- Adafruit_BMP085.h > https://github.com/adafruit/Adafruit-BMP085-Library

Die Sketch datei uns in breich MAC und IPAddres angepass weden.

Beitrag auf meie WEB-Seite : http://anic.tk/2p5XKQN or https://www.philipp-lindner.de/2021/08/18/52-wetterstation-mit-arduino-und-esp.html

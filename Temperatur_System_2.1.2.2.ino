/*
 * Temperatur System mit DS18B20
 * Autor: Philipp Linener post@philipp-lindner.de
 * www.philipp-lindmer.de
 */

 /*
  * CONFIG und Include
  */
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <dht11.h>
#include <Adafruit_BMP085.h>

OneWire oW(7);
DallasTemperature sen(&oW);

const int cS = 4;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFF }; //<< MAC: DE:AD:BE:EF:FE:FF
IPAddress ip(192, 168, xxx, xxx); //<< xxx= IP aud ihren Home Netzwerk Bereich eintragen
EthernetServer server(80);

dht11 DHT11;
#define DHT11PIN 6

Adafruit_BMP085 bmp;

//LED

int led1 = 13;
int led2 = 12;
int led3 = 12;
int led4 = 10;
int led5 = 9;
int led6 = 8;

//seriennummer
String serNum ="xxxx"; //<< Selbst Generien 13 Stellige Zalen Und Buchstaben.

//SoftwerVersion
String SofV="2.1.2.1";
 
/*
  * PROGRAM
 */
  
void setup() {
  Serial.begin(9600);

  //LED def Audgänge

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  
  //Server
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("Temperatur System by Philipp Lindner");
  Serial.println("Seriennummer:");
  Serial.print(serNum);
  Serial.println("Softverversion:");
  Serial.print(SofV);
  Serial.println("Server Gestartet unter IP: ");
  Serial.print(Ethernet.localIP());
  
  
//Sensoren:
 sen.begin();
  Serial.println("\nSensoren Gestartet....");

  if (!bmp.begin()) {
  Serial.println("Der BMP085 (LUFTDRUCKSENSOR) hat eine Tchneisches Problem");
  while (1) {}
  }

  
  //SD Carte
 Serial.println("Initalizing SD Karte...");
  if(!SD.begin(cS)){
    Serial.println("Keine SD Carte!");
    return;
  }
  Serial.println("Card Initalized");
 
}

void loop() {
  //LED AUS
  digitalWrite(led1, LOW);
  //Sensoren
  sen.requestTemperatures();
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Temp 1:");
  Serial.println(sen.getTempCByIndex(0));
  Serial.println("Temp 2:");
  Serial.println(sen.getTempCByIndex(1));
  Serial.println("Temp 3:");
  Serial.println(sen.getTempCByIndex(2));
  Serial.println("Temp 4:");
  Serial.println(sen.getTempCByIndex(3));
  Serial.println("Temp 5:");
  Serial.println(sen.getTempCByIndex(4));
  Serial.print("Temp DHT11: ");
  Serial.print((float)DHT11.temperature, 2);
  Serial.print(" C");
  Serial.print("RelF: ");
  Serial.print((float)DHT11.humidity, 2);
  Serial.print(" %");
  Serial.print("Pressure: ");
  Serial.println(bmp.readPressure());

  String data ="";
         
   for (int i = 0; i<5; i++)
   {
      data +=sen.getTempCByIndex(i);
      data +=",";
      date +=dht.readHumidity();
      data +=",";
   }
   data +=(float)DHT11.humidity, 2;
   data +=",";
   data +=(float)DHT11.temperature, 2;
   data +=",";
   data +=bmp.readPressure();
   data +="";

  File dF = SD.open("templog.csv", FILE_WRITE);
  if (dF)
  {
    dF.println(data);
    dF.close();
    Serial.println("Daten Geschreiben");
  }
  else
  {
    Serial.println("Date NICHT Geschiben");
  } 
 
  
  // WEB Aufruf:
 // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/xml");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<Tempsys>");
          String data2 ="";
          
   for (int i = 0; i<5; i++)
   {
      data2 +="<tem";
      data2 +=i;
      data2 +=">";
      data2 +=sen.getTempCByIndex(i);
      data2 +="</tem";
      data2 +=i;
      data2 +=">";
   }
          client.println(data2);
          client.println("<luftF>");
          client.println((float)DHT11.humidity, 2);
          client.println("</luftF>");
          client.println("<luftT>");
          client.println((float)DHT11.temperature, 2);
          client.println("</luftT>");
          client.println("<luftD>");
          client.println(bmp.readPressure());
          client.println("</luftD>");
          client.println("<seriennummer>");
          client.println(serNum);
          client.println("</seriennummer>");
          client.println("<Softverversion>");
          client.println(SofV);
          client.println("</Softverversion>");
          client.println("</Tempsys>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  digitalWrite(led1,HIGH);
    delay(1000);
}

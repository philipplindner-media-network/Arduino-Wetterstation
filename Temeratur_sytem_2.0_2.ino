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
#include <DHT.h>
#include <Adafruit_BMP085.h>



OneWire oW(7);
DallasTemperature sen(&oW);

const int cS = 4;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFF };
IPAddress ip(192, 168, 178, 70);
EthernetServer server(80);

long randNumber;
/*
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPON,DHTTYPE);
Adafruit-BMP085 bmp;
*/
 
/*
 * PROGRAM
 */
  
void setup() {
  Serial.begin(9600);
  
  //Server
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("Temperatur System by Philipp Lindner");
  Serial.println("Server Gestartet unter IP: ");
  Serial.print(Ethernet.localIP());
  
  
//Sensoren:
  sen.begin();
  Serial.println("Sensoren Gestartet....");

  /*
   * dht.begin();
   * bmp.begin();
   */

  
  //SD Carte
  Serial.println("Initalizing SD Karte...");
  if(!SD.begin(cS)){
    Serial.println("Keine SD Carte!");
    return;
  }
  Serial.println("Card Initalized");
  
}

void loop() {
  //Sensoren
  sen.requestTemperatures();

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

  /*
   * Serial.println("Temperatur 6:");
   * Serial.println(dht.readTemperature());
   * Serial.println("Luftfeuchtigkeit:");
   * Serial.println(dht.readHumidity());
   * Serial.println("Luftdruck:");
   * Serial.println(bmp.readPressure());
   */

  String data ="";
  randNumber = random(300);
         
   for (int i = 0; i<5; i++)
   {
      data +=i;
      data +=",";
      data +=sen.getTempCByIndex(i);
      data +=",";
    //data +=dht.readTemperature();
    //data +=",";
    //date +=dht.readHumidity();
    //data +=",";
    //data +=bmp.readPressure();
      data +=randNumber;
   }
   data +="|-|";

  File dF = SD.open("templog.tsSC", FILE_WRITE);
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
 

  //TWITTER BEITRAG vom System 
  
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
      data2 +="|";
      data2 +=millis();;
      data2 +="</tem";
      data2 +=i;
      data2 +=">";
   }
          client.println(data2);
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
  
   delay(1000);
}


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h>

// wireless network credentials:
const char* ssid = "WLNA";
const char* password = "PASSWORD";


// hostname for this system:
const char* host = "tempsensor01";

// data wire is connected with GPIO2:
#define ONE_WIRE_BUS 2

// setup one wire instance:
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// web server on port 80:
ESP8266WebServer server(80);

float getTemperature()
{
  float temperature;

  // request temperature:
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  return temperature;
}

String getContent()
{
  //ESP ID Sammlung
  String EspID01="FF41F984DC826";
  String EspID02="HCHCXBCHHDFH0";
  String EspID03="NLZTFVXHMACM2";
  String EspID04="SLODEVHUIHJT6";
  // get temperature and convert to string:
  char stringBuffer[6];
  dtostrf(getTemperature(), 2, 2, stringBuffer);

  // create content for the website
  String content = "<Termeratur><temp id='"+EspID01+"'> ";
  content += stringBuffer;
  content += "</temp><lufF></lufF></Termeratur>";

  return content;
}


void setup()
{
  // initialize DS1820 sensor with 12 bit resolution:
  Serial.begin(115200);
  sensors.begin();
  sensors.setResolution(12);

  // connect to the wireless network:
  WiFi.begin(ssid, password);

  // wait for wireless network connection:
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println("System Gestartet");
  Serial.println("System IP: ");
  Serial.println(WiFi.localIP());


  // initialize mDNS:
  MDNS.begin(host);
  MDNS.addService("http", "tcp", 80);

  // start HTTP server:
  server.begin();

  // print start page:
  server.on("/", [](){
    server.send(200, "text/xml", getContent());
  });
}

void loop()
{
  // handle HTTP request:
  server.handleClient();
}

#define DEBUG_WIFI 1

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define HTTP_REST_PORT 80

ESP8266WebServer server(HTTP_REST_PORT);

bool ready = false;

IPAddress ip(192, 168, 0, 1);
IPAddress ip_zero(0, 0, 0, 0);
IPAddress subnet(255, 255, 255, 0);

String ssid = "XRobotics";
String pw = "projectalpha";

void getHelloWord() 
{
    server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}

void restServerRouting() 
{
    server.on("/", HTTP_GET, []() 
    {
      server.send(200, F("text/html"),F("Welcome to the REST Web Server"));
    });
    server.on(F("/helloWorld"), HTTP_GET, getHelloWord);
}

bool setupWifi() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip_zero, subnet);
  return WiFi.softAP("XRobotics", "projectalpha");
}

void setupSerial() {

}

void setupServer() {
    ready = true;
    Serial.println("Ready");
    delay(1000);
    restServerRouting();

    server.begin();
    Serial.println(WiFi.softAPIP().toString());
}

void setup() 
{
  // pinMode(16, OUTPUT);
  // pinMode(5, OUTPUT);

  Serial.begin(9600);
  Serial.println();

  //Wifi setup
  Serial.print("Setting soft-AP ... ");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip_zero, subnet);
  boolean result = setupWifi();
  if(result == true)
  {
    setupServer();
  }
  else
  {
    Serial.println("Failed!");
  }
}

void loop() 
{
  if (ready) 
  {
    server.handleClient();
  }

  // String input = Serial.readString();
  // Serial.println(input);
  // input.trim();
  // if (input == "on") {
  //   digitalWrite(16, HIGH);
  //   digitalWrite(5, HIGH);
  // } else if (input == "off") {
  //   digitalWrite(16, LOW);
  //   digitalWrite(5, LOW);
  // }
}
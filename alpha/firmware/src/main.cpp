#define DEBUG_WIFI 1

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include "pins.h"
#define HTTP_REST_PORT 80

ESP8266WebServer server(HTTP_REST_PORT);

bool ready = false;

IPAddress ip(192, 168, 0, 1);
IPAddress ip_zero(0, 0, 0, 0);
IPAddress subnet(255, 255, 255, 0);

String ssid = "XRobotics";
String pw = "projectalpha";

Servo servo1;

void getHelloWord()
{
  server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}
void handleLed1On()
{
  digitalWrite(LED_YELLOW, HIGH);
  server.send(200, "text/plain", "ok");
}
void handleLed1Off()
{
  digitalWrite(LED_YELLOW, LOW);
  server.send(200, "text/plain", "ok");
}
void handleLed2On()
{
  digitalWrite(LED_BLUE, HIGH);
  server.send(200, "text/plain", "ok");
}
void handleLed2Off()
{
  digitalWrite(LED_BLUE, LOW);
  server.send(200, "text/plain", "ok");
}
void handleServo()
{ // Handler for the body path

  if (server.hasArg("plain") == false)
  { // Check if body received

    server.send(200, "text/plain", "Body not received");
    return;
  }
  String message = server.arg("plain");
  int servoAngle = message.toInt();
  servo1.write(servoAngle);
  // Serial.println(message);
  server.send(200, "text/plain", "ok");
}

void restServerRouting()
{
  server.on("/", HTTP_GET, []()
            { server.send(200, F("text/html"), F("Welcome to the REST Web Server")); });
  server.on(F("/helloWorld"), HTTP_GET, getHelloWord);
  server.on(F("/led1/on"), HTTP_GET, handleLed1On);
  server.on(F("/led1/off"), HTTP_GET, handleLed1Off);
  server.on(F("/led2/on"), HTTP_GET, handleLed2On);
  server.on(F("/led2/off"), HTTP_GET, handleLed2Off);
  server.on(F("/servo"), HTTP_POST, handleServo);
}
bool setupWifi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip_zero, subnet);
  return WiFi.softAP("XRobotics", "projectalpha");
}

void setupSerial()
{
}

void setupServer()
{
  ready = true;
  Serial.println("Ready");
  delay(1000);
  restServerRouting();

  server.begin();
  Serial.println(WiFi.softAPIP().toString());
}

void setup()
{
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(4, OUTPUT);
  servo1.attach(4);

  Serial.begin(9600);
  Serial.println();

  // Wifi setup
  Serial.print("Setting soft-AP ... ");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip_zero, subnet);
  boolean result = setupWifi();
  if (result == true)
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
  //   digitalWrite(LED_YELLOW, HIGH);
  //   digitalWrite(LED_BLUE, HIGH);
  // } else if (input == "off") {
  //   digitalWrite(LED_YELLOW, LOW);
  //   digitalWrite(LED_BLUE, LOW);
  // }
}
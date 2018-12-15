/*#include <WiFi.h>

const char ssid[] = "ESP32AP-AGATSUMA";
const char pass[] = "21111111";
const IPAddress ip(192,168,0,1);
const IPAddress subnet(255,255,255,0);
WiFiServer server(80);
int count = 0;

void setup()
{
  Serial.begin(115200);
  WiFi.softAP(ssid,pass);
  delay(100);
  WiFi.softAPConfig(ip,ip,subnet);
  IPAddress serverIP = WiFi.softAPIP();
  server.begin();

  Serial.println();
  Serial.print("AccessPoint:");
  Serial.println(ssid);
  Serial.print("IP:");
  Serial.println(serverIP);
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("new request");
  while(!client.available()){
    delay(1);
  }

  String res = "";
  while(client.available()) {
      char c = client.read(); 
      res += c;
  }
  Serial.println(res);

  client.print("HTTP/1.1 200 OK\r\n");
  client.print("Content-Type: text/html; charset=utf-8;\r\n");
  client.print("\r\n");
  count++;
  client.println(count);
}
*/

/*
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char ssid[] = "ESP32AP-AGATSUMA";
const char pass[] = "21111111";
const IPAddress ip(192,168,0,1);
const IPAddress subnet(255,255,255,0);
WebServer server(80);
const char page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width,initial-scale=1">
</head>
<body>
<center>
LED<br>
<a href="/on">ON</a><br>
<a href="/off">OFF</a><br>
</center>

</body>
</html>
)=====";

void handleRoot() {
  server.send(200, "text/html", page);
}

void handleOn(){
  digitalWrite(4, HIGH);
  Serial.println("LED ON");
  server.send(200, "text/html", page);
}

void handleOff(){
  digitalWrite(4, LOW);
  Serial.println("LED OFF");
  server.send(200, "text/html", page);
}

void setup()
{
  Serial.begin(115200);
  WiFi.softAP(ssid,pass);
  delay(100);
  WiFi.softAPConfig(ip,ip,subnet);
  IPAddress serverIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();

  pinMode(4, OUTPUT);

  Serial.println();
  Serial.print("AccessPoint:");
  Serial.println(ssid);
  Serial.print("IP:");
  Serial.println(serverIP);
}

void loop() {
  server.handleClient();
}
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char ssid[] = "ESP32AP-AGATSUMA";
const char pass[] = "21111111";
const IPAddress ip(192,168,0,1);
const IPAddress subnet(255,255,255,0);
WebServer server(80);
const char page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width,initial-scale=1">
</head>
<body>
<center>
LED<br>
<a href="/?led=on">ON</a><br>
<a href="/?led=off">OFF</a><br>
</center>

</body>
</html>
)=====";

void handleRoot() {
  if (server.hasArg("led")) {
      String led = server.arg("led");
      Serial.println(led);
      if(led == "on") {
        digitalWrite(4, HIGH);
      } else if(led == "off") {
        digitalWrite(4, LOW);
      }
  }
  server.send(200, "text/html", page);
}

void setup()
{
  Serial.begin(115200);
  WiFi.softAP(ssid,pass);
  delay(100);
  WiFi.softAPConfig(ip,ip,subnet);
  IPAddress serverIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.begin();

  pinMode(4, OUTPUT);

  Serial.println();
  Serial.print("AccessPoint:");
  Serial.println(ssid);
  Serial.print("IP:");
  Serial.println(serverIP);
}

void loop() {
  server.handleClient();
}

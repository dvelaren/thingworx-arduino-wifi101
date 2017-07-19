/**********************************************************************************************************
ThingworxWiFi101.h - Library for uploading values to a ThingWorx "Thing" via WiFi 101 modules
Created by David Velasquez 19/7/2017 for
Universidad EAFIT
www.eafit.edu.co

Create a service in your Thing or ThingShape and create inputs that will match the variable names you use
in your Arduino code.  In the JavaScript window type something similar to the following:

me.PropertyOne = parseFloat(InputOne);
me.PropertyTwo = parseFloat(InputTwo);

Where Property one is the name of your first Thing or ThingShape property and InputOne is the name of
your first input.  Everything is case sensitive.
************************************************************************************************************/

#include "ThingWorxWiFi101.h"

ThingWorx::ThingWorx(char* server, int port, char* appKey, char* thingName, char* serviceName) {
  _server = server;
  _port = port;
  _appKey = appKey;
  _thingName = thingName;
  _serviceName = serviceName;
}

void ThingWorx::post(int sensorCount, char* sensorNames[], float values[]) {
  String url = "/Thingworx/Things/";
  String body = "";
  url += thingName;
  url += "/Services/";
  url += serviceName;
  for (int idx = 0; idx < sensorCount; idx++) {
    if (idx != 0) body += "&";
    body += propertyNames[idx];
    body += "=";
    body += values[idx];
  }
  if (_client.connect(_server, _port)) {
    Serial.println("Connected to:" + String(_server) + ":" + String(_port));
    //Send the HTTP POST request:

    _client.print(String("POST ") + url + " HTTP/1.1\r\n" +
    "Host: " + _server + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "Content-Length: " + body.length() + "\r\n" +
    "Connection: close\r\n" +
    "appKey: " + _appKey + "\r\n\r\n" +
    body + "\r\n\r\n");

    Serial.print(String("POST ") + url + " HTTP/1.1\r\n" +
    "Host: " + _server + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "Content-Length: " + body.length() + "\r\n" +
    "Connection: close\r\n" +
    "appKey: " + _appKey + "\r\n\r\n" +
    body + "\r\n\r\n");
  }
  unsigned long timeout = millis();
  while (_client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      _client.stop();
      return;
    }
  }
  while (_client.available()) {
    String line = _client.readStringUntil('\r');
    Serial.print(line);
  }
  else {
    Serial.println("The connection could not be established");
    _client.stop();
  }
}

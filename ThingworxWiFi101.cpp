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

The REST API documentation was obtained from:
https://support.ptc.com/appserver/cs/view/solution.jsp?n=CS249622&art_lang=en&posno=1&q=Thingworx%20post%20request%20arduino&ProductFamily=ThingWorx%7CNRN%7CAxeda&source=search

GET Request example:
GET /Thingworx/Things/MyThing/Properties/MyProperty HTTP/1.1
Host: thingworx.myserver.com
Accept: application/json
Connection: close
appKey: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx

POST Request example:
POST /Thingworx/Things/MyThing/Services/MyService HTTP/1.1
Host: thingworx.myserver.com
Content-Type: application/x-www-form-urlencoded
Content-Length: 27
Connection: close
appKey: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx

MY_PARAM1=123&MY_PARAM2=abc
************************************************************************************************************/

#include "ThingWorxWiFi101.h"

ThingWorx::ThingWorx(char* server, int port, char* appKey, char* thingName, char* serviceName) {
  _server = server;
  _port = port;
  _appKey = appKey;
  _thingName = thingName;
  _serviceName = serviceName;
}

void ThingWorx::post(const int sensorCount, char* sensorNames[], float values[]) {
  String url = "/Thingworx/Things/";
  String body = "";
  url += _thingName;
  url += "/Services/";
  url += _serviceName;
  for (int idx = 0; idx < sensorCount; idx++) {
    if (idx != 0) body += "&";
    body += sensorNames[idx];
    body += "=";
    body += values[idx];
  }
  if (_client.connect(_server, _port)) {
    Serial.println("Connected to: " + String(_server) + ":" + String(_port));
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
    _client.stop();
  }
  else {
    Serial.println("The connection could not be established");
    _client.stop();
  }
}

String ThingWorx::getjson() {
  return getjson("");
}

String ThingWorx::getjson(String property) {
  String url = "/Thingworx/Things/";
  url += _thingName;
  url += "/Properties/";
  url += property;
  if (_client.connect(_server, _port)) {
    Serial.println("Connected to: " + String(_server) + ":" + String(_port));

    //Send the HTTP GET request:
    _client.print(String("GET ") + url + " HTTP/1.1\r\n" +
    "Host: " + _server + "\r\n" +
    "Accept: application/json\r\n" +
    "Connection: close\r\n" +
    "appKey: " + _appKey + "\r\n\r\n");

    Serial.print(String("GET ") + url + " HTTP/1.1\r\n" +
    "Host: " + _server + "\r\n" +
    "Accept: application/json\r\n" +
    "Connection: close\r\n" +
    "appKey: " + _appKey + "\r\n\r\n");

    unsigned long timeout = millis();
    while (_client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        _client.stop();
        return "Error";
      }
    }
    String json = "";
    boolean httpBody = false;
    while (_client.available()) {
      String line = _client.readStringUntil('\r');
      Serial.print(line);
      if (!httpBody && line.charAt(1) == '{') {
        httpBody = true;
      }
      if (httpBody) {
        json += line;
        httpBody = false;
      }
    }
    return json;
  }
  else {
    Serial.println("The connection could not be established");
    _client.stop();
  }
}

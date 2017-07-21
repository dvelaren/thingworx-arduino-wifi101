# thingworx-arduino-wifi101
Arduino library using REST API to send and receive data to Thingworx platform 8. It allows to send and receive multiple variables with the provided methods.

## Requirements

* [Arduino MKR1000](https://store.arduino.cc/usa/arduino-mkr1000) or [Arduino WiFi101 Shield](https://www.arduino.cc/en/Main/ArduinoWiFiShield101).
* [Arduino UNO](http://www.arduino.org/products/boards/arduino-uno) or [Arduino Mega](https://www.arduino.cc/en/Main/arduinoBoardMega) if using WiFi101 Shield.
* [Arduino IDE 1.8.3 or higher](https://www.arduino.cc/en/Main/Software).
* [Thingworx Arduino WiFi101 Library](https://github.com/tidusdavid/thingworx-arduino-wifi101).

## REST API for Thingworx 8

The REST API implemented in this library follows this format:

GET request
```javascript
  GET /Thingworx/Things/MyThing/Properties/MyProperty HTTP/1.1
  Host: thingworx.myserver.com
  Accept: application/json
  Connection: close
  appKey: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
```

POST request
```javascript
  POST /Thingworx/Things/MyThing/Services/MyService HTTP/1.1
  Host: thingworx.myserver.com
  Content-Type: application/x-www-form-urlencoded
  Content-Length: 27
  Connection: close
  appKey: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx

  MY_PARAM1=123&MY_PARAM2=abc
```

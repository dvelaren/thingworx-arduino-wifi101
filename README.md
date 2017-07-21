# thingworx-arduino-wifi101
Arduino library using REST api to send and receive data to Thingworx platform 8. It can communicate multiple variables.
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

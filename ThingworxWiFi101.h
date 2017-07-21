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

#ifndef ThingworxWiFi101_h
#define ThingworxWiFi101_h

#include "Arduino.h"
#include "SPI.h"
#include "WiFi101.h"
#include "string.h"

class ThingWorx {
	public:
		ThingWorx(char* server, int port, char* appKey, char* thingName, char* serviceName = "");
		void post(const int sensorCount, char* sensorNames[], float values[]);
		String getjson();
		String getjson(String property);
		//void get(const int inputCount, char* inputNames[], float *inputValues);	To be implemented

	private:
    WiFiClient _client;
		char* _server;
    int _port;
		char* _appKey;
		char* _thingName;
		char* _serviceName;
};

#endif

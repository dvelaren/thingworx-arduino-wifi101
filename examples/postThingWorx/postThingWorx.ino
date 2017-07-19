//Name: postThingWorx
//Author: David Velasquez
//Date: 19/07/2017
//Description: This program sends 2 sensor vars to Thingworx Server.

//Libraries
#include <ThingworxWiFi101.h>

//I/O pin labeling
#define POT 0 //Potentiometer connected to pin A0

//Server Constants
const unsigned long TPOST = 5000;  //Time between requests to TWX server (every 5 secs)
const unsigned int sensorCount = 2;  //Number of sensor vars to send to TWX server (2)
char* ssid = "Change to your SSID"; //WiFi SSID
char* password = "Change to your pass"; //WiFi Pass
char* host = "Change to your twx host";  //TWX Host example: myhost.edu.co (without http at beginning)
unsigned int port = 80; //TWX host port

//Variables
//->TWX Vars
char appKey[] = "Write your TWX API key here"; //API Key from TWX
char thingName[] = "Name of your TWX Thing";  //Thing name from TWX
char serviceName[] = "Name of your TWX Service";  //Thing service name from TWX
char* propertyNames[] = {"INPUT1 name", "INPUT2 name"};  //Input names vector created on service from TWX (check names on TWX service)
float propertyValues[sensorCount]; //Vector to store sensor vars to be sent to TWX
//->Timing Vars
unsigned long lastConnectionTime = 0; //Last connection ms time between server requests
//->ThingworxWiFi101 Vars
ThingWorx myThing(host, port, appKey, thingName, serviceName);  //Declare the TWX object with his corresponding properties

//Subroutines & functions
void printWifiStatus() {
  //Print SSID name
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  //Print ipv4 assigned to WiFi101 module
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  //Print signal strength for WiFi101 module
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void WiFiInit() {
  delay(1000);  //Wait 1 sec for module initialization

  //Check if WiFi Shield is connected to Arduino
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    //Infinite loop if shield is not detected
    while (true);
  }

  //Attempt a WiFi connection to desired access point at ssid, password
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, password);
    delay(10000); //Wait 10 secs for establishing connection
  }
  //Print WiFi status
  printWifiStatus();
}

void setup() {
  //I/O configuration

  //Physical outputs initialization

  //Communications
  Serial.begin(9600); //Serial communications with computer at 9600 bauds for debug purposes
  WiFiInit(); //WiFi communications initialization
}

void loop() {
  //propertyValues[0] = analogRead(POT) * 100.0 / 1023.0; //Uncomment if using real potentiometer at A0 pin
  propertyValues[0] = 24; //Comment if using real potentiometer
  propertyValues[1] = 88; //Write a constant value to the second sensor var
  if (millis() - lastConnectionTime > TPOST) {  //Send request to server every TPOST seconds
    myThing.post(sensorCount, propertyNames, propertyValues); //Send values to server platform
    lastConnectionTime = millis();  //Refresh last connection time
  }
}

//Name: getThingWorxJSONLib
//Author: David Velasquez
//Date: 23/07/2017
//Description: This program gets 2 variables from Thingworx server and reflects the first one as a PWM on LED
//Requires ArduinoJson library

//Libraries
#include <ThingworxWiFi101.h>
#include <ArduinoJson.h>

//I/O pin labeling

//Server Constants
const unsigned long TPOST = 5000;  //Time between requests to TWX server (every 5 secs)
const unsigned int READCOUNT = 2; //Number of variables to be read from thingworx (2)
char* ssid = "Change to your SSID"; //WiFi SSID
char* password = "Change to your pass"; //WiFi Pass
char* host = "Change to your twx host";  //TWX Host example: myhost.edu.co (without http at beginning)
unsigned int port = 80; //TWX host port

//Variables
//->TWX Vars
char appKey[] = "Write your TWX API key here"; //API Key from TWX
char thingName[] = "Name of your TWX Thing";  //Thing name from TWX
char* writeNames[READCOUNT] = {"READVAR1 name", "READVAR2 name"};  //Name of the variables to be read from the thingworx server
unsigned int writeValues[READCOUNT] = {0, 0};  //Thingworx read variables values converted to unsigned int
String inputJson = "";  //Variable to store Input Properties JSON
//->Timing Vars
unsigned long lastConnectionTime = 0; //Last connection ms time between server requests
//->ThingworxWiFi101 Vars
ThingWorx myThing(host, port, appKey, thingName);  //Declare the TWX object with his corresponding properties

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
  pinMode(LED_BUILTIN, OUTPUT); //Built in LED from board as output

  //Physical outputs initialization
  digitalWrite(LED_BUILTIN, LOW); //Turn off built in LED

  //Communications
  Serial.begin(9600); //Serial communications with computer at 9600 bauds for debug purposes
  WiFiInit(); //WiFi communications initialization
}

void loop() {
  if (millis() - lastConnectionTime > TPOST) {  //Send request to server every TPOST seconds
    inputJson = myThing.getjson(); //Get all properties from server platform
    //inputJson = myThing.getjson("write1"); //Get 1 property with write1 label from server platform
    Serial.println(inputJson);
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(inputJson);
    if (root.success()) for (int i = 0; i < READCOUNT; i++) writeValues[i] = root["rows"][0][writeNames[i]];  //Extract each variable value from the JSON and store it on the corresponding var
    else Serial.println("Error parsing json");
    Serial.println("write1: " + String(writeValues[0]) + " write2: " + String(writeValues[1]));
    //writeValues[0] = root["rows"][0][writeNames[0]];
    //Serial.println("write1: " + String(writeValues[0]));
    analogWrite(LED_BUILTIN, writeValues[0]); //Reflect thingworx variable as PWM in onboard led
    lastConnectionTime = millis();  //Refresh last connection time
  }
}

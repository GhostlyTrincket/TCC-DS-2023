//code obtained from: https://github.com/KrisKasprzak/ESP32_WebPage
#include <WiFi.h>
#include <WebServer.h>
#include "Main_Page.h"

//#define SENSOR_PIN 36

IPAddress actual_ip;
IPAddress page_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress ip;

WebServer server(80);

#define WIFI_NAME "HOMERSIMPSON"
#define WIFI_PASSWORD "4D2A1BC2"

char xml[2048]; // buffer for XML operations
char buffer[64]; // buffer to make operations (add stuff to the XML)

//char* soil_status = "";
///int soil_moisture = analogRead(SENSOR_PIN);
int soil_moisture = 413;
//const int bad_soil = 1230;
//const int good_soil = 2460;
//const int very_good_soil = 3690;

void setup() {
	Serial.begin(9600);

	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED) { Serial.print('.'); } // while it's not connected to wifi, try to connect to it. We don't need to do nothin' inside this loop 'cause we don't do this process manually!

	Serial.print("\nGo to: ");
	Serial.println(WiFi.localIP());

	actual_ip = WiFi.localIP();

	server.on("/", send_website);
	server.on("/xml", send_xml);

	server.begin();
}

void loop() {
	server.handleClient();
}

void send_website() {
	Serial.println("Sending HTML");

	server.send(200, "text/html", MAIN_PAGE);
}

void send_xml() {
	Serial.println("Sending XML");

	strcpy(xml, "<?xml version = '1.0'?>\n<Data>\n"); // must keep. xml header.

//  https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
  sprintf(buffer, "<Moisture>%d</Moisture>", soil_moisture); 
	strcat(xml, buffer);

/*
stuff for later... maybe
  sprintf(buffer, "<SoilStatus>%s</SoilStatus>, soil_status);
  strcat(xml, buffer);
*/

	strcat(xml, "</Data>\n");
	server.send(200, "text/xml", xml);
}
